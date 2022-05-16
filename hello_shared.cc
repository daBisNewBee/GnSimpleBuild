// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "hello_shared.h"

const char* GetSharedText() {
#if ENABLE_DOOM_MELON
  return "enable_doom_melon";
#else
  return "disable_doom_melon";
#endif
}
