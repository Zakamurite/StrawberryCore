/*
 * Copyright (C) 2010-2012 Strawberry-Pr0jcts <http://strawberry-pr0jcts.com/>
 * Copyright (C) 2005-2012 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "PacketWorker.h"
#include "WorldPacket.h"
#include "ObjectGuid.h"

void PacketWorker::BuildSetMovementPacket(Opcodes op, WorldPacket* data, ObjectGuid guid, uint32 value)
{
    switch(op)
    {
        case SMSG_FORCE_MOVE_ROOT:
        {
            uint8 guidMask[8] = { 2, 7, 6, 0, 5, 4, 1, 3 };
            uint8 byteOrder[8] = { 1, 0, 2, 5, 3, 4, 7, 6 };
            data->WriteGuidMask(guid.GetRawValue(), guidMask, 8);
            data->WriteGuidBytes(guid.GetRawValue(), byteOrder, 4, 0);
            *data << uint32(value);
            data->WriteGuidBytes(guid.GetRawValue(), byteOrder, 4, 4);
            data->FlushBits();
            break;
        }
        case SMSG_FORCE_MOVE_UNROOT:
        {
            uint8 guidMask[8] = { 0, 1, 3, 7, 5, 2, 4, 6 };
            uint8 byteOrder[8] = { 3, 6, 1, 2, 0, 7, 4, 5 };
            data->WriteGuidMask(guid.GetRawValue(), guidMask, 8);
            data->WriteGuidBytes(guid.GetRawValue(), byteOrder, 3, 0);
            *data << uint32(value);
            data->WriteGuidBytes(guid.GetRawValue(), byteOrder, 5, 3);
            break;
        }
        default:
        {
            sLog.outError("Called PacketWorker::BuildSetMovementPacket for unknown opcode %u", op);
            break;
        }
    }
}

void PacketWorker::BuildSendPlayVisual(WorldPacket* data, ObjectGuid guid, uint32 value, bool impact)
{
    *data << uint32(0);         // unk, seems always 0
    *data << uint32(value);
    *data << uint32(impact ? 1 : 0);

    uint8 guidMask[8] = { 4, 7, 5, 3, 1, 2, 0, 6 };
    uint8 byteOrder[8] = { 0, 4, 1, 6, 7, 2, 3, 5 };
    data->WriteGuidMask(guid.GetRawValue(), guidMask, 8);
    data->WriteGuidBytes(guid.GetRawValue(), byteOrder, 8, 0);
}
