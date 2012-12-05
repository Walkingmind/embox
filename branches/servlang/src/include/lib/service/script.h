#ifndef LIB_SERVICE_SCRIPT_H_
#define LIB_SERVICE_SCRIPT_H_

#define SERVICE_MAX_VARS 10
#define SERVICE_VAR_LEN 64
#define SERVICE_FILE_NAME_LEN 256
#define SERVICE_SCRIPT_SENTINEL '#'

enum service_variable_type {SRV_VAR_NAN, SRV_VAR_INT, SRV_VAR_STRING, SRV_VAR_BOOL, SRV_VAR_FLOAT, SRV_VAR_MAX};

struct service_variable {
	char name[SERVICE_VAR_LEN];
	char value[SERVICE_VAR_LEN];
	enum service_variable_type type;
};

struct service_script {
	service_variable vars[SERVICE_MAX_VARS];
	char script_file[SERVICE_FILE_NAME_LEN];
	int vars_count;
};

extern int service_script_init (struct sevice_script * srv_scrpt, const char * script_file);
extern int service_script_preprocess_file (struct service_script * srv_scrpt, const char * out_file_name, struct variable vars[]);
extern char * service_script_get_variable (struct service_script * srv_scrpt, const char * name);
extern int service_script_get_vars_from_query (struct service_script * srv_scrpt, const char * query);
extern int service_script_get_vars_count(struct service_script * srv_scrpt);
extern int service_script_get_vars_left(struct service_script * srv_scrpt);

#endif
