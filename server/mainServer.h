#ifndef MAINSERVER
#define MAINSERVER

#include <microhttpd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <iostream>
#include <fstream>
#include <ctime>
#include <mutex> 

#include "config.h"

//following this tutorial:
//https://www.gnu.org/software/libmicrohttpd/tutorial.html

enum Connectiontype {POST, GET};

struct connection_info_struct
{
  Connectiontype connectiontype;
  char *answerstring;
  struct MHD_PostProcessor *postprocessor;
};

/* used by load_file to find out the file size */
long get_file_size (const char *filename);

/* used to load the key files into memory */
char* load_file (const char *filename);

/*inline void convert_Pointers(void* cls);*/
/*inline void convert_Objects(void* cls);*/

/* check if a the password and username are correct */
inline int authorised_connection(struct MHD_Connection* connection);
												 
/* This funct is called when a url is requested, it handles what happens on the
   side. At the end of this function a respons is send to the user */
int answer_to_connection(void* cls,struct MHD_Connection* connection, const char* url,
												 const char* method, const char* version, const char* upload_data,
												 size_t* upload_data_size, void** con_cls);

/* called to process post request data */
static int iterate_post(void *coninfo_cls, enum MHD_ValueKind kind, const char *key,
												const char *filename, const char *content_type,
												const char *transfer_encoding, const char *data, 
												uint64_t off, size_t size);

/* cleans up memory used by post call */
void request_completed(void *cls, struct MHD_Connection *connection, 
     		        			 void **con_cls, enum MHD_RequestTerminationCode toe);

void* toVoidArr(std::ofstream* outfile);

inline void fromVoidArr(void* cls, std::ofstream*& outfile);

#endif

