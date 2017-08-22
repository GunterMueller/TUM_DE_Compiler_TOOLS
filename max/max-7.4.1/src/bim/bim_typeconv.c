


/* ================================================================ */
/* Konvertierung von Bitmap-Ressourcen				    */
/* ================================================================ */
static Boolean strToPixmap(Display *dpy, XrmValue *args, Cardinal *num_args, 
			   XrmValue *from, XrmValue *to, 
			   XtPointer *converter_data)
 {
  Pixmap pixmap;
  int width,height;
  int dummy;
  extern Screen * screen_for_convert;

  if ((to->addr == NULL || to->size < sizeof(Pixmap)) &&
      (to->addr = (XtPointer) malloc(sizeof(Pixmap))) == NULL)
    return False;;   
  pixmap = XmuLocatePixmapFile(screen_for_convert,
                               (char *)from->addr,
                               BlackPixelOfScreen(screen_for_convert),
                               WhitePixelOfScreen(screen_for_convert),
                               DefaultDepthOfScreen(screen_for_convert),
                               NULL,0,
                               &width,&height,
                               &dummy,&dummy);
  if (pixmap)
   {
    *(Pixmap *)to->addr = pixmap;
    to->size = sizeof(Pixmap);
    return True;
   }
  else
   {
    String name = (String)from->addr;
    Cardinal num = 1;

    XtAppWarningMsg(XtDisplayToApplicationContext(dpy),
                    "strToPixmap", "noPixmap", "XtToolkitError",
                    "Cannot get Pixmap \"%s\"", \
                    &name, &num);
    return False;
   }
 } /* strToPixmap */



