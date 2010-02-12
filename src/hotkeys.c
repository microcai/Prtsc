#include <X11/Xlib.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include "hotkeys.h"
#include <string.h>

gchar*
keycode_to_string(KeyCode keycode, GtkWidget* widget)
{
    gchar *keyname;
    KeySym sym;
    Display *display;

    keyname = NULL;
    display = widget ? GDK_DISPLAY_XDISPLAY(gtk_widget_get_display(widget)) : GDK_DISPLAY();
    sym = XKeycodeToKeysym(display, keycode, 0);
    if (sym != NoSymbol)
        keyname = XKeysymToString(sym);

    return keyname;
}

gboolean
parse_keystr(const gchar* keystr, GtkWidget* widget, HotkeyEntry* key)
{
    Display* display;
    KeySym sym;

    display = widget ? GDK_DISPLAY_XDISPLAY(gtk_widget_get_display(widget)) : GDK_DISPLAY();
    if (!display)
        return FALSE;

    if (strlen(keystr) < 1)
        return FALSE;
  
    sym = XStringToKeysym(keystr);
    if (sym == NoSymbol)
	    return FALSE;

    key->code = XKeysymToKeycode(display, sym);
    if (!key->code)
	    return FALSE;

    return TRUE;
}

static gboolean grab_key(int mod, int code )
{
    Display* display;
    Window root;

    display = gdk_x11_get_default_xdisplay();
    root = DefaultRootWindow(display);

    code = XKeysymToKeycode(display,code);


    gdk_error_trap_push();

    XGrabKey(display, code, mod, root, True,
	     GrabModeAsync, GrabModeAsync);


	XGrabKey(display, code, mod | Mod2Mask, root, True, GrabModeAsync,
			GrabModeAsync);
	XGrabKey(display, code, mod | Mod5Mask, root, True, GrabModeAsync,
			GrabModeAsync);
	XGrabKey(display, code, mod | LockMask, root, True, GrabModeAsync,
			GrabModeAsync);
	XGrabKey(display, code, mod | Mod2Mask | LockMask, root, True,
			GrabModeAsync, GrabModeAsync);
	XGrabKey(display, code, mod | Mod5Mask | LockMask, root, True,
			GrabModeAsync, GrabModeAsync);
	XGrabKey(display, code, mod | Mod2Mask | Mod5Mask, root, True,
			GrabModeAsync, GrabModeAsync);
	XGrabKey(display, code, mod | Mod2Mask | Mod5Mask | LockMask, root, True,
			GrabModeAsync, GrabModeAsync);
	gdk_flush();

	if (gdk_error_trap_pop())
		return FALSE;

    return TRUE;
}

static int same_modifier(int mod ,int state)
{
	return TRUE;
}

void prase_hotkey(XKeyEvent * event, HotkeyEntry*entry, int num)
{
	g_printf("prase_hotkey, code = %d state = %d\n",event->keycode,event->state);
	int i;
	for(i=0;i<num;++i)
	{
		if	( event->keycode == XKeysymToKeycode(event->display,entry[i].code)  && same_modifier(entry[i].mod,event->state) )
		{
			g_printf("hot key press\n");
			entry[i].hotkeyfunc(entry[i].user_data);
		}
	}
}

int		register_hotkey(HotkeyEntry* entry,int num)
{
	int i;
	for(i=0;i<num;++i)
	{
		grab_key(entry[i].mod,entry[i].code);
	}
}

int		unregister_hotkey(HotkeyEntry* entry,int num)
{
    Display* display;
    Window root;


    display = gdk_x11_get_default_xdisplay();
    root = DefaultRootWindow(display);

	int i;
	for(i=0;i<num;++i)
	{
		XUngrabKey(display,AnyKey, AnyModifier,root);
	}
}
