// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stdio.h>

#include "hello_shared.h"
#include "hello_static.h"
#include <string>
#include <iostream>

enum Type {
  NONE = 0,
  NETWORK,                  // No connectivity.
  INITIALIZATION_ERROR,     // The translation script failed to initialize.
  UNKNOWN_LANGUAGE,         // The page's language could not be detected.
  UNSUPPORTED_LANGUAGE,     // The server detected a language that the browser
                            // does not know.
  IDENTICAL_LANGUAGES,      // The original and target languages are the same.
  TRANSLATION_ERROR,        // An error was reported by the translation script
                            // during translation.
  TRANSLATION_TIMEOUT,      // The library doesn't finish initialization.
  UNEXPECTED_SCRIPT_ERROR,  // The library raises an unexpected exception.
  BAD_ORIGIN,               // The library is blocked because of bad origin.
  SCRIPT_LOAD_ERROR,        // Loader fails to load a dependent JavaScript.
  TRANSLATE_ERROR_MAX,
  TYPE_LAST = TRANSLATE_ERROR_MAX
};


using namespace std;

int main(int argc, char* argv[]) {
  printf("%s, %s\n", GetStaticText(), GetSharedText());

  std::string msg = "a";
  msg += "zz";
  std::cout << "msg += zz" << msg << endl; // zzazz ?

  std::string msg2 = "b";
  msg2 = msg2 + "zz";
  std::cout << "msg2 = msg2 + zz = " << msg2 << endl;  // bzz

  std::string msg3;
  msg3.append("a");
  msg3.append("b");
  msg3.append("c");
  std::cout << "msg3 append = " << msg3 << endl; // abc

  Type error = Type::UNKNOWN_LANGUAGE;
  // std::string enumMsg = static_cast<typename std::underlying_type<Type>::type>(error);
  // long enumMsg = error;
  long enumMsg = static_cast<long>(error);
  std::cout << "enumMsg = " << enumMsg << endl;

  return 0;
}
