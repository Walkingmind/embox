#include <string.h>
#include <stdio.h>

#include <lib/service/service.h>
#include <embox/web_service.h>
#include <framework/mod/options.h>


#define TEMPLATE_FILE OPTION_STRING_GET(template_file)

#define VAR_COUNT 10
#define VAR_LEN 20

#define PP_SENTINEL '#'

struct variable {
	char name[VAR_LEN];
	char value[VAR_LEN];
}; 

static const char *get_variable_by_name(const struct variable *vars, const char *name) {
	int i;
	for (i = 0; i < VAR_COUNT; i++) {
		if (!strcmp(vars[i].name, name))
			return vars[i].value;
	}
	return NULL;
}

static void get_variables_from_query(const char * query, struct variable * vars) {
	int i, qptr, len;
	char * dump;
	printf("Query :: %s\n", query);

	for (i = 0; i < VAR_COUNT; i++) {
		vars[i].name[0] = '\0';
		vars[i].value[0] = '\0';
	}

	if (query) {
		qptr = 0;
		for (i = 0; query[qptr] && i < VAR_COUNT; i++) {
			dump = vars[i].name;
			len = 0;
			for (; query[qptr] && query[qptr] != '&'; qptr++) {
				if (query[qptr] == '=') {
					dump[len] = '\0';
					dump = vars[i].value;
					len = 0;
				} else {
					if (len < VAR_LEN - 1) {
						dump[len] = query[qptr];
						len++;
					} else if (len == VAR_LEN - 1) {
						dump[len] = '\0';
					}
				}
				if (query[qptr+1] == '\0' || query[qptr+1] == '&') {
					dump[len] = '\0';
				}
			}
			if (query[qptr] == '&')
				qptr++;
		}
	}
}

static void print_var (struct variable * vars, int i) {
	printf("Name:  %s\nValue: %s\n\n", vars[i].name, vars[i].value);
}

static void print_vars (struct variable * vars) {
	int i;
	for (i = 0; i < VAR_COUNT; i++) {
		if (vars[i].name[0] || vars[i].value[0]) {
			print_var(vars, i);
		}
	}
}

static void preprocess_file(FILE *out, struct variable *vars) {
	char t;
	int escaped = 0, len = 0;
	char var[VAR_LEN];
	const char * val;
	FILE *in;

	if( 0 == (in = fopen(TEMPLATE_FILE, "r"))) {
		return;
	}

	for (t = fgetc(in); t != EOF; t = fgetc(in)) {
		if (t == PP_SENTINEL) {
			if (escaped) {
				if (len == 0) {
					fputc(PP_SENTINEL, out);
				} else {
					var[len] = '\0';
					val = get_variable_by_name(vars, var);
					if (val) {
						fwrite(val, strlen(val) * sizeof(char), 1, out);
					}
					len = 0;
				}
				escaped = 0;
			} else {
				escaped = 1;
			}
		} else {
			if (escaped) {
				if (len < VAR_LEN - 1) {
					var[len] = t;
					len++;
				}
			} else {
				fputc(t, out);
			}
		}
	}
	fclose(in);
}

static void * entry_point(void *arg) {
	struct service_data *srv_data;
	struct service_file srv_file;
	struct variable vars[VAR_COUNT];

	srv_data = (struct service_data *)arg;

	if (service_file_open_write(&srv_file) < 0) {
		service_free_service_data(srv_data);
		return NULL;
	}

	get_variables_from_query(srv_data->query, vars);
	print_vars(vars);

	preprocess_file(srv_file.fd, vars);
	srv_data->http_status = HTTP_STAT_200;

	if (service_file_switch_to_read_mode(&srv_file) < 0) {
		service_free_service_data(srv_data);
		return NULL;
	}

	service_send_reply(srv_data, &srv_file);

	service_free_resourses(srv_data, &srv_file);

	return NULL;
}

int new_service_is_started;

EMBOX_WEB_SERVICE("new.html", &new_service_is_started, entry_point);
