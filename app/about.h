/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __ABOUT_H__
#define __ABOUT_H__

#define GLIMPSE_NAME \
  _("Glimpse")

#define GLIMPSE_SUBTITLE \
  _("A Free and Open Source image editor")

/* The year of the last commit (UTC) will be inserted into this string. */
#define GLIMPSE_COPYRIGHT \
  _("Copyright © 2020 Glimpse Contributors\n" \
    "Based on GNU Image Manipulation Program " \
    GIMP_VERSION)

/* TRANSLATORS: do not end the license URL with a dot, because it would
 * be in the link. Because of technical limitations, make sure the URL
 * ends with a space, a newline or is end of text.
 * Cf. bug 762282.
 */
#define GLIMPSE_LICENSE \
  _("Glimpse is free software: you can redistribute it and/or modify it "   \
    "under the terms of the GNU General Public License as published by " \
    "the Free Software Foundation; either version 3 of the License, or " \
    "(at your option) any later version."                                \
    "\n\n"                                                               \
    "Glimpse is distributed in the hope that it will be useful, "           \
    "but WITHOUT ANY WARRANTY; without even the implied warranty of "    \
    "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the "     \
    "GNU General Public License for more details."                       \
    "\n\n"                                                               \
    "You should have received a copy of the GNU General Public License " \
    "along with Glimpse. If not, see: https://www.gnu.org/licenses/")


#endif /* __ABOUT_H__ */
