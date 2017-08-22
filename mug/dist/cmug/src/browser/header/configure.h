#ifndef CONFIGURE_H
#define CONFIGURE_H

/*
 * (c) copyright 1995 by Technische Universitaet Muenchen, Germany
 *
 *	This product is part of MUGBrowser
 *	MUGBrowser is a part of the compiler writing system
 *	MUG (Modularer Uebersetzer-Generator, TU Muenchen)
 *
 * Permission to use, duplicate or disclose this software must be
 * obtained in writing. Requests for such permissions may be sent to
 *
 *	Prof. Dr. J. Eickel
 *	Institut fuer Informatik
 *	Technische Universitaet Muenchen
 *	D-80290 Muenchen
 *	Germany
 *
 * No version of this implementation may be used or distributed for gain,
 * all listings must contain our copyright notice, and the headings
 * produced by MUG-Modules must contain the text "MUG" and "TU - Muenchen".
 */

/* procedure prototypes */

int get_image(ALEP a, ANList *list);
void image_refresh(TEP wurzel, ANList *anlist);
void config_equal(ANList *list, ALEP a, int image);
int config_save(ANList *list, char *file);
int config_load(ANList *list, char *file);
void config_init(ANList *list);

#endif
