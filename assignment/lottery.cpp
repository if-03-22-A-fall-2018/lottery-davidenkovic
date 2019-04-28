/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			lottery.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * Implementation of a library for analyzing lottery tips.
 *-----------------------------------------------------------------------------
*/

#include <stdio.h>
#include "lottery.h"

char separator;
int tip[TIP_SIZE];
FILE* fd;

#define 	UUID_LEN   40
#define 	MAX_TIP_LEN   17
#define 	MAX_LINE_LEN   (UUID_LEN + 1 + MAX_TIP_LEN + 1)

int char_to_int(char* chars, int count){
  int num=0;
  for (int i = 0; i < count; i++) {
    num=num*10+chars[i]-'0';
  }
  return num;
}
int search_start(char* line){
  for (int i = 0; i < MAX_LINE_LEN; i++) {
    if(line[i]==separator){
      return i+1;
    }
  }
  return -1;
}
bool is_in_drawings(int tips){
  for (int i = 0; i < TIP_SIZE; i++) {
    if(tips==tip[i])
    {
      return true;
    }
  }
  return false;
}
bool init_lottery (const char *csv_file, char csv_separator){
  fd=fopen(csv_file,"r");
  separator=csv_separator;

  for (int i = 0; i < TIP_SIZE; i++) {
    tip[i]=0;
  }
  return fd!=0;
}
bool get_tip (int tip_number, int tip[TIP_SIZE]){
  char line[MAX_LINE_LEN];
  fseek(fd, 0 , SEEK_SET);
  if(tip_number<0){
    return false;
  }

  for (int i = 0; i <= tip_number; i++) {
    if(fgets(line, MAX_LINE_LEN, fd) == 0)
    {
      return false;
    }
  }
  int index=0;
  int count=0;
  for (int i = search_start(line); i < MAX_LINE_LEN; i++) {
    char numbers[2];
    if(line[i]==separator || line[i]=='\n' || line[i]=='\0'){
      tip[index++]=char_to_int(numbers,count);
      count=0;
      if(index==TIP_SIZE){
        break;
      }
    }
    else{
      numbers[count++]=line[i];
    }
  }
  return true;
}
bool set_drawing (int drawing_numbers[TIP_SIZE]){
  for (int i = 0; i < TIP_SIZE; i++) {
    if(drawing_numbers[i]<1 || drawing_numbers[i] > 45){
      return false;
    }
    tip[i]=drawing_numbers[i];
  }
  return true;
}
int get_tip_result (int tip_number){
  if(tip[0]==0){
    return -1;
  }

  int tips[TIP_SIZE];

  if(!get_tip(tip_number,tips)){
    return -2;
  }

  int count=0;

  for (int i = 0; i < TIP_SIZE; i++) {
    if(is_in_drawings(tips[i])){
      count++;
    }
  }
}
int get_right_tips_count (int right_digits_count){
  return 0;
}
