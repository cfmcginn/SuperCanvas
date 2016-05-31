#ifndef CHECKMAKEDIR_H
#define CHECKMAKEDIR_H

#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "include/globalDoDebug.h"

struct stat st;

bool checkDir(const std::string inPath)
{
  if(stat(inPath.c_str(), &st) != 0) return false;

  if(st.st_mode & S_IFDIR) return true;
  else return false;
}

bool checkFile(const std::string inFile)
{
  if(stat(inFile.c_str(), &st) != 0) return false;

  if(st.st_mode & S_IFREG) return true;
  else return false;
}


bool checkMakeDir(const std::string inPath)
{
  bool dirIsMade = false;
  
  if(checkFile(inPath)){
    std::cout << "Path \'" << inPath << "\' already exists as file. Return false." << std::endl;
  }
  else if(checkDir(inPath)) dirIsMade = true;
  else if(!checkDir(inPath)){
    mkdir(inPath.c_str(), 0700);
    dirIsMade = true;
  }

  return dirIsMade;
}

#endif
