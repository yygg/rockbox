/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 * $Id$
 *
 * Copyright (C) 2007 by Christian Gmeiner
 *
 * All files in this archive are subject to the GNU General Public License.
 * See the file COPYING in the source tree root for full license agreement.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ****************************************************************************/

#ifndef _STORGAGE_H_
#define _STORGAGE_H_

#include "usbstack/core.h"

/* register storage driver in usb stack */
void usb_storage_driver_init(void);

int usb_storage_driver_bind(void* controller_ops);
void usb_storage_driver_unbind(void);
int usb_storage_driver_request(struct usb_ctrlrequest* req);
void usb_storage_driver_speed(enum usb_device_speed speed);

#endif /*_STORGAGE_H_*/
