/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis
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

/* NOTE: This file is auto-generated by pdbgen.pl. */

#include "config.h"

#include <cairo.h>
#include <string.h>

#include <gegl.h>

#include <gdk-pixbuf/gdk-pixbuf.h>

#include "libgimpcolor/gimpcolor.h"

#include "libgimpbase/gimpbase.h"

#include "pdb-types.h"

#include "core/gimp.h"
#include "core/gimpcontainer-filter.h"
#include "core/gimpcontext.h"
#include "core/gimpdatafactory.h"
#include "core/gimppalette.h"
#include "core/gimpparamspecs.h"

#include "gimppdb.h"
#include "gimppdb-utils.h"
#include "gimpprocedure.h"
#include "internal-procs.h"


static GimpValueArray *
palettes_refresh_invoker (GimpProcedure         *procedure,
                          Gimp                  *gimp,
                          GimpContext           *context,
                          GimpProgress          *progress,
                          const GimpValueArray  *args,
                          GError               **error)
{
  gimp_data_factory_data_refresh (gimp->palette_factory, context);

  return gimp_procedure_get_return_values (procedure, TRUE, NULL);
}

static GimpValueArray *
palettes_get_list_invoker (GimpProcedure         *procedure,
                           Gimp                  *gimp,
                           GimpContext           *context,
                           GimpProgress          *progress,
                           const GimpValueArray  *args,
                           GError               **error)
{
  gboolean success = TRUE;
  GimpValueArray *return_vals;
  const gchar *filter;
  gint32 num_palettes = 0;
  gchar **palette_list = NULL;

  filter = g_value_get_string (gimp_value_array_index (args, 0));

  if (success)
    {
      palette_list = gimp_container_get_filtered_name_array (gimp_data_factory_get_container (gimp->palette_factory),
                                                             filter, &num_palettes);
    }

  return_vals = gimp_procedure_get_return_values (procedure, success,
                                                  error ? *error : NULL);

  if (success)
    {
      g_value_set_int (gimp_value_array_index (return_vals, 1), num_palettes);
      gimp_value_take_stringarray (gimp_value_array_index (return_vals, 2), palette_list, num_palettes);
    }

  return return_vals;
}

static GimpValueArray *
palettes_get_palette_invoker (GimpProcedure         *procedure,
                              Gimp                  *gimp,
                              GimpContext           *context,
                              GimpProgress          *progress,
                              const GimpValueArray  *args,
                              GError               **error)
{
  gboolean success = TRUE;
  GimpValueArray *return_vals;
  gchar *name = NULL;
  gint32 num_colors = 0;

  GimpPalette *palette = gimp_context_get_palette (context);

  if (palette)
    {
      name       = g_strdup (gimp_object_get_name (palette));
      num_colors = gimp_palette_get_n_colors (palette);
    }
  else
    success = FALSE;

  return_vals = gimp_procedure_get_return_values (procedure, success,
                                                  error ? *error : NULL);

  if (success)
    {
      g_value_take_string (gimp_value_array_index (return_vals, 1), name);
      g_value_set_int (gimp_value_array_index (return_vals, 2), num_colors);
    }

  return return_vals;
}

static GimpValueArray *
palettes_get_palette_entry_invoker (GimpProcedure         *procedure,
                                    Gimp                  *gimp,
                                    GimpContext           *context,
                                    GimpProgress          *progress,
                                    const GimpValueArray  *args,
                                    GError               **error)
{
  gboolean success = TRUE;
  GimpValueArray *return_vals;
  const gchar *name;
  gint32 entry_num;
  gchar *actual_name = NULL;
  gint32 num_colors = 0;
  GimpRGB color = { 0.0, 0.0, 0.0, 1.0 };

  name = g_value_get_string (gimp_value_array_index (args, 0));
  entry_num = g_value_get_int (gimp_value_array_index (args, 1));

  if (success)
    {
      GimpPalette *palette;

      if (name && strlen (name))
        palette = gimp_pdb_get_palette (gimp, name, FALSE, error);
      else
        palette = gimp_context_get_palette (context);

      if (palette)
        {
          GimpPaletteEntry *entry = gimp_palette_get_entry (palette, entry_num);

          if (entry)
            {
              actual_name = g_strdup (gimp_object_get_name (palette));
              num_colors  = gimp_palette_get_n_colors (palette);
              color       = entry->color;
            }
          else
            success = FALSE;
        }
      else
        success = FALSE;
    }

  return_vals = gimp_procedure_get_return_values (procedure, success,
                                                  error ? *error : NULL);

  if (success)
    {
      g_value_take_string (gimp_value_array_index (return_vals, 1), actual_name);
      g_value_set_int (gimp_value_array_index (return_vals, 2), num_colors);
      gimp_value_set_rgb (gimp_value_array_index (return_vals, 3), &color);
    }

  return return_vals;
}

void
register_palettes_procs (GimpPDB *pdb)
{
  GimpProcedure *procedure;

  /*
   * gimp-palettes-refresh
   */
  procedure = gimp_procedure_new (palettes_refresh_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-palettes-refresh");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-palettes-refresh",
                                     "Refreshes current palettes. This function always succeeds.",
                                     "This procedure retrieves all palettes currently in the user's palette path and updates the palette dialogs accordingly.",
                                     "Adrian Likins <adrian@gimp.org>",
                                     "Adrian Likins",
                                     "1998",
                                     NULL);
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-palettes-get-list
   */
  procedure = gimp_procedure_new (palettes_get_list_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-palettes-get-list");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-palettes-get-list",
                                     "Retrieves a list of all of the available palettes",
                                     "This procedure returns a complete listing of available palettes. Each name returned can be used as input to the command 'gimp-context-set-palette'.",
                                     "Nathan Summers <rock@gimp.org>",
                                     "Nathan Summers",
                                     "2001",
                                     NULL);
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_string ("filter",
                                                       "filter",
                                                       "An optional regular expression used to filter the list",
                                                       FALSE, TRUE, FALSE,
                                                       NULL,
                                                       GIMP_PARAM_READWRITE));
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_int32 ("num-palettes",
                                                          "num palettes",
                                                          "The number of palettes in the list",
                                                          0, G_MAXINT32, 0,
                                                          GIMP_PARAM_READWRITE));
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_string_array ("palette-list",
                                                                 "palette list",
                                                                 "The list of palette names",
                                                                 GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-palettes-get-palette
   */
  procedure = gimp_procedure_new (palettes_get_palette_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-palettes-get-palette");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-palettes-get-palette",
                                     "Deprecated: Use 'gimp-context-get-palette' instead.",
                                     "Deprecated: Use 'gimp-context-get-palette' instead.",
                                     "",
                                     "",
                                     "",
                                     "gimp-context-get-palette");
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_string ("name",
                                                           "name",
                                                           "The palette name",
                                                           FALSE, TRUE, FALSE,
                                                           NULL,
                                                           GIMP_PARAM_READWRITE));
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_int32 ("num-colors",
                                                          "num colors",
                                                          "The palette num_colors",
                                                          G_MININT32, G_MAXINT32, 0,
                                                          GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-palettes-get-palette-entry
   */
  procedure = gimp_procedure_new (palettes_get_palette_entry_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-palettes-get-palette-entry");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-palettes-get-palette-entry",
                                     "Deprecated: Use 'gimp-palette-entry-get-color' instead.",
                                     "Deprecated: Use 'gimp-palette-entry-get-color' instead.",
                                     "",
                                     "",
                                     "",
                                     "gimp-palette-entry-get-color");
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_string ("name",
                                                       "name",
                                                       "The palette name (\"\" means currently active palette)",
                                                       FALSE, TRUE, FALSE,
                                                       NULL,
                                                       GIMP_PARAM_READWRITE));
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_int32 ("entry-num",
                                                      "entry num",
                                                      "The entry to retrieve",
                                                      G_MININT32, G_MAXINT32, 0,
                                                      GIMP_PARAM_READWRITE));
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_string ("actual-name",
                                                           "actual name",
                                                           "The palette name",
                                                           FALSE, FALSE, FALSE,
                                                           NULL,
                                                           GIMP_PARAM_READWRITE));
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_int32 ("num-colors",
                                                          "num colors",
                                                          "The palette num_colors",
                                                          G_MININT32, G_MAXINT32, 0,
                                                          GIMP_PARAM_READWRITE));
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_rgb ("color",
                                                        "color",
                                                        "The color requested",
                                                        FALSE,
                                                        NULL,
                                                        GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);
}
