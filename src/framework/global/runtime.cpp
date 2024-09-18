/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-CLA-applies
 *
 * MuseScore
 * Music Composition & Notation
 *
 * Copyright (C) 2021 MuseScore BVBA and others
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "runtime.h"

#ifdef Q_OS_LINUX
#include <pthread.h>
#endif

static thread_local std::string s_threadName;

void muse::runtime::setThreadName(const std::string& name)
{
    s_threadName = name;
#ifdef Q_OS_LINUX
    // Set thread name through pthreads to aid debuggers that display such names.
    // Thread names are limited to 16 bytes on Linux, including the
    // terminating null.
    std::string truncated_name = name.length() > 15 ? name.substr(0, 15) : name;
    if (pthread_setname_np(pthread_self(), truncated_name.c_str()) > 0) {
        qWarning() << Q_FUNC_INFO << "Couldn't set thread name through pthreads";
    }
#endif
}

const std::string& muse::runtime::threadName()
{
    if (s_threadName.empty()) {
        static thread_local std::string id = toString(std::this_thread::get_id());
        return id;
    }
    return s_threadName;
}
