#include <stdio.h>
#include <stdlib.h>
#include "addressbook.pb-c.h"
#define MAX_MSG_SIZE 4096

//typedef struct Tutorial__AddressBook Addressbook;
//typedef struct Tutorial__Person Person;
//typedef struct Tutorial__Person__PhoneNumber PhoneNumber;



/*
// UNTESTED
static_size_t
read_file (char *filename, unsigned max_length, uint8_t *out)
{
    int i, rc;
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }
    for (i = 0; (rc = getc(fp)) != EOF && i < max_length; buffer[i++] = rc) { }
    fclose(fp);
    return EXIT_SUCCESS;
}
*/


static size_t
read_buffer (unsigned max_length, uint8_t *out)
{
  size_t cur_len = 0;
  uint8_t c, nread;
  while ((nread=fread(out + cur_len, 1, max_length - cur_len, stdin)) != 0)
    {
      cur_len += nread;
      if (cur_len == max_length)
        {
          fprintf(stderr, "max message length exceeded\n");
          exit(1);
        }
    }
  return cur_len;
}


int main (int argc, const char * argv[])
{
  //AddressBook *msg;
  Tutorial__AddressBook *msg;

  // Read packed message from standard-input.
  uint8_t *buf = malloc(MAX_MSG_SIZE);
  size_t msg_len = read_buffer (MAX_MSG_SIZE, buf);
  //size_t msg_len = read_file ("amessage1.proto", MAX_MSG_SIZE, buf);
  Tutorial__Person *curr_person;
  int i;

  // Unpack the message using protobuf-c.
  msg = tutorial__address_book__unpack(NULL, msg_len, buf);
  if (msg == NULL)
    {
      fprintf(stderr, "error unpacking incoming message\n");
      exit(1);
    }

  // display the message's fields.
  i = 0;
  while (i < msg->n_person) {
//  for (curr_person = msg->person[i]; ; curr_person = msg->person[++i]) {
    curr_person = msg->person[i];
    printf("Id : %d\n", curr_person->id);
    printf("Name : %s\n", curr_person->name);
    printf("Email : %s\n", curr_person->email);
    printf("\n");
    i++;
  }

  // Free the unpacked message
  tutorial__address_book__free_unpacked(msg, NULL);
  free(buf);
  return 0;
}

