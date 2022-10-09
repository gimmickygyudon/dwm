/* See LICENSE file for copyright and license details. */

/* appearance */
static const char font[]        = "JetBrainsMono Nerd Font:size=9";
static const char* normbgcolor  = "#282a36";
static const char* normfgcolor  = "#6272a4";
static const char* selbgcolor   = "#44475a";
static const char* selfgcolor   = "#bd93f9";
static const char* urgbgcolor   = "#ff5555";
static const char* urgfgcolor   = "#44475a";
static const char before[]      = "";
static const char after[]       = "";
static const char titletrim[]   = "...";
static const int  tabwidth      = 200;
static const int barHeight		= 24;
static const Bool foreground    = True;
static       Bool urgentswitch  = False;

/*
 * Where to place a new tab when it is opened. When npisrelative is True,
 * then the current position is changed + newposition. If npisrelative
 * is False, then newposition is an absolute position.
 */
static int  newposition   = 0;
static Bool npisrelative  = False;

#define SETPROP(p) { \
        .v = (char *[]){ "/bin/sh", "-c", \
                "prop=\"`xwininfo -children -id $1 | grep '^     0x' |" \
                "sed -e's@^ *\\(0x[0-9a-f]*\\) \"\\([^\"]*\\)\".*@\\1 \\2@' |" \
                "xargs -0 printf %b | dmenu -l 10 -w $1`\" &&" \
                "xprop -id $1 -f $0 8s -set $0 \"$prop\"", \
                p, winid, NULL \
        } \
}

#define MODKEY Mod1Mask
static const Key keys[] = {
	/* modifier             key        function     argument */
	{ MODKEY,				XK_d, 	   focusonce,   { 0 } },
	{ MODKEY,				XK_d,      spawn,       { 0 } },

	{ MODKEY|ShiftMask,     XK_Right,  rotate,      { .i = +1 } },
	{ MODKEY|ShiftMask,     XK_Left,   rotate,      { .i = -1 } },
	{ MODKEY|ShiftMask,     XK_j,      movetab,     { .i = -1 } },
	{ MODKEY|ShiftMask,     XK_k,      movetab,     { .i = +1 } },
	{ MODKEY|ControlMask,   XK_Tab,    rotate,      { .i = 0 } },

	{ MODKEY,               XK_grave,  spawn,       SETPROP("_TABBED_SELECT_TAB") },
	{ MODKEY|ControlMask,   XK_1,      move,        { .i = 0 } },
	{ MODKEY|ControlMask,   XK_2,      move,        { .i = 1 } },
	{ MODKEY|ControlMask,   XK_3,      move,        { .i = 2 } },
	{ MODKEY|ControlMask,   XK_4,      move,        { .i = 3 } },
	{ MODKEY|ControlMask,   XK_5,      move,        { .i = 4 } },
	{ MODKEY|ControlMask,   XK_6,      move,        { .i = 5 } },
	{ MODKEY|ControlMask,   XK_7,      move,        { .i = 6 } },
	{ MODKEY|ControlMask,   XK_8,      move,        { .i = 7 } },
	{ MODKEY|ControlMask,   XK_9,      move,        { .i = 8 } },
	{ MODKEY|ControlMask,   XK_0,      move,        { .i = 9 } },

	{ MODKEY,               XK_q,      killclient,  { 0 } },

	{ MODKEY,               XK_u,      focusurgent, { 0 } },
	{ MODKEY|ShiftMask,     XK_u,      toggle,      { .v = (void*) &urgentswitch } },

	{ 0,                    XK_F11,    fullscreen,  { 0 } },
};
