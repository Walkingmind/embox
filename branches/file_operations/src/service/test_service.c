/**
 * @file
 *
 * @date Nov 8, 2012
 * @author: Vita Loginova
 */

#include <embox/web_service.h>
#include <string.h>
#include <lib/expat.h>

struct test_service_data {
	struct service_data * srv_data;
	struct service_file * srv_file;
};

static void start_element(void *userData, const char *name, const char **atts) {
	struct test_service_data * data = (struct test_service_data *) userData;
	int i = 0;

	if (strcmp(name, "c:out") == 0) {
		//param -> text
		fwrite(data->srv_data->query, sizeof(char),
				strlen(data->srv_data->query), data->srv_file->fd);
	} else {
		//open tag
		fwrite("<", sizeof(char), 1, data->srv_file->fd);
		fwrite(name, sizeof(char), strlen(name), data->srv_file->fd);

		//add atts
		while (atts[i] != NULL) {
			fwrite(" ", sizeof(char), 1, data->srv_file->fd);
			fwrite(atts[i], sizeof(char), strlen(atts[i]), data->srv_file->fd);
			fwrite("=\"", sizeof(char), 2, data->srv_file->fd);
			i++;
			fwrite(atts[i], sizeof(char), strlen(atts[i]), data->srv_file->fd);
			fwrite("\"", sizeof(char), 1, data->srv_file->fd);
			i++;
		}

		fwrite(">", sizeof(char), 1, data->srv_file->fd);
	}
}

static void end_element(void *userData, const char *name) {
	struct test_service_data * data = (struct test_service_data *) userData;

	if (strcmp(name, "c:out") != 0) {
		//close tag
		fwrite("</", sizeof(char), 2, data->srv_file->fd);
		fwrite(name, sizeof(char), strlen(name), data->srv_file->fd);
		fwrite(">", sizeof(char), 1, data->srv_file->fd);
	}
}

static void character(void *userData, const XML_Char *s, int len) {
	struct test_service_data * data = (struct test_service_data *) userData;

	//text between tags
	fwrite(s, sizeof(char), len, data->srv_file->fd);
}

static void *process_params(void* args) {
	struct test_service_data data;
	struct service_data srv_data;
	struct service_file srv_file;
	char buf[512];
	int done;
	XML_Parser parser;
	FILE *input;
	const char in_file[] = "test.html";

	data.srv_data = &srv_data;
	data.srv_file = &srv_file;

	service_get_service_data(&srv_data, args);
	service_file_open_write(&srv_file);

	parser = XML_ParserCreate(NULL);
	XML_SetHTMLUse(parser);
	XML_SetUserData(parser, &data);
	XML_SetElementHandler(parser, start_element, end_element);
	XML_SetCharacterDataHandler(parser, character);

	input = fopen(in_file, "r");
	do {
		int len = (int) fread(buf, 1, sizeof(buf), input);
		done = len < sizeof(buf);
		if (XML_Parse(parser, buf, len, done) == XML_STATUS_ERROR) {
			XML_ParserFree(parser);
			service_send_error(&srv_data, &srv_file);
			service_close_connection(&srv_data);
			service_file_close(&srv_file);
			break;
		}
	} while (!done);

	XML_ParserFree(parser);
	service_file_switch_to_read_mode(&srv_file);
	service_send_reply(&srv_data, &srv_file);
	service_close_connection(&srv_data);
	service_file_close(&srv_file);
	return NULL;
}

EMBOX_WEB_SERVICE("test.html", process_params);
