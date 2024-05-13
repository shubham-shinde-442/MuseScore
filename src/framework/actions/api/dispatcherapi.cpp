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
#include "dispatcherapi.h"

#include "log.h"

using namespace muse::api;
using namespace muse::actions;
using namespace muse::actions::api;

DispatcherApi::DispatcherApi(muse::api::IApiEngine* e)
    : muse::api::ApiObject(e)
{
}

void DispatcherApi::dispatch(const QString& action, const QVariantList& args)
{
    ActionData data;
    int index = 0;

    for (const QVariant& arg : args) {
        switch (arg.typeId()) {
        case QMetaType::Int: data.setArg<int>(index, arg.value<int>());
            break;
        default: {
            LOGE() << "unknown type: " << arg.typeName();
            continue;
        } break;
        }

        ++index;
    }

    dispatcher()->dispatch(action.toStdString(), data);
}
