/* See LICENSE file for copyright and license details. */

/* alt-tab configuration */
static const unsigned int tabModKey 		= 0x40;	/* if this key is hold the alt-tab functionality stays acitve. This key must be the same as key that is used to active functin altTabStart `*/
static const unsigned int tabCycleKey 		= 0x17;	/* if this key is hit the alt-tab program moves one position forward in clients stack. This key must be the same as key that is used to active functin altTabStart */
static const unsigned int tabPosY 			= 1;	/* tab position on Y axis, 0 = bottom, 1 = center, 2 = top */
static const unsigned int tabPosX 			= 1;	/* tab position on X axis, 0 = left, 1 = center, 2 = right */
static const unsigned int maxWTab 			= 600;	/* tab menu width */
static const unsigned int maxHTab 			= 200;	/* tab menu height */

/* appearance */

#include <X11/XF86keysym.h>

static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappx     = 30;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=14" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#999999";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};


/* tagging */
char *tags[] = {
  "1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9", "10"
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"alacritty", "--class", "quick", "-e", "tmux", NULL };
const char *spcmd2[] = {"chromium", "--user-data-dir=/home/kayon/chrome/whats", "--app=https://web.whatsapp.com", "--class=whatsapp", NULL };
const char *spcmd3[] = {"discord", NULL };
const char *spcmd4[] = {"slack", NULL };
const char *spcmd5[] = {"dolphin", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"quick",      spcmd1},
	{"whatsapp",      spcmd2},
	{"discord",      spcmd3},
	{"slack",      spcmd4},
	{"dolphin",      spcmd5},
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Emacs",       NULL,    NULL,        1 << 1,          0,          0 },
	{ "pavucontrol",       NULL,    NULL,        1 << 5,          0,          0 },
	{ ".blueman-manager-wrapped",       NULL,    NULL,        1 << 5,          0,          0 },
	{ "obsidian",       NULL,    NULL,        1 << 3,          0,          0 },
	{ "DBeaver",       NULL,    NULL,        1 << 3,          0,          0 },
	{ "obs",       NULL,    NULL,        1 << 4,          0,          0 },
	{ "KeePassXC",       NULL,    NULL,        1 << 4,          0,          0 },
	{ "Vial",       NULL,    NULL,        1 << 4,          0,          0 },

	{ "quick",	      NULL,    NULL,      SPTAG(0),		1,	   -1 },
	{ "whatsapp",    NULL,	  NULL,      SPTAG(1),		1,	   -1 },
	{ NULL,	    "discord",	  NULL,	     SPTAG(2),		1,	   -1 },
	{ NULL,	      "slack",	  NULL,	     SPTAG(3),		1,	   -1 },
	{ NULL,	      "dolphin",	  NULL,	     SPTAG(4),		1,	   -1 },
};

/* layout(s) */
static const float mfact     = 0.48; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	{ "[M]",      monocle },
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL, NULL},
};

/* key definitions */
#define MODKEY Mod4Mask
/* #define TAGKEYS(KEY,TAG) \ */
/* 	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \ */
/* 	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \ */
/* 	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \ */
/* 	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, */

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      tag,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },


/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };

// laptop
// static const char *roficmd[] = { "rofi", "-dpi", "192", "-show", "drun", "-show-icons", NULL };
// static const char *aroficmd[] = { "rofi", "-dpi", "192", "-show", "window", "-show-icons", NULL };

// desktop
static const char *roficmd[] = { "rofi", "-show", "drun", "-show-icons", NULL };
static const char *aroficmd[] = { "rofi", "-show", "window", "-show-icons", NULL };

static const char *termcmd[]  = { "alacritty", NULL };

static const char *printwhole[]  = { "flameshot","full", "-c", NULL };
static const char *printarea[]  = { "flameshot", "gui", NULL };

static const char *upvol[]      = { "wpctl",   "set-volume", "@DEFAULT_SINK@",      ".05+",      NULL };
static const char *downvol[]      = { "wpctl",   "set-volume", "@DEFAULT_SINK@",      ".05-",      NULL };
static const char *mutevol[]      = { "/usr/bin/pactl",   "set-sink-volume", "@DEFAULT_SINK@",      "toggle",      NULL };
static const char *play[]    = { "playerctl", "play-pause", NULL };

#include "movestack.c"
static const Key keys[] = {
	/* modifier                     key        function        argument */
	// Printing
	{ 0,                         XK_Print,      spawn,      {.v = printwhole } },
	{ 0|ShiftMask,               XK_Print,      spawn,      {.v = printarea  } },

	// Media keys
	{ 0,               XF86XK_AudioLowerVolume, spawn,      {.v = downvol    } },
	{ 0,               XF86XK_AudioMute,        spawn,      {.v = mutevol    } },
	{ 0,               XF86XK_AudioRaiseVolume, spawn,      {.v = upvol      } },
	{ 0,               XF86XK_AudioPlay,        spawn,      {.v = play       } },

	// num row


	{ MODKEY,                       XK_apostrophe,      cyclelayout,     {.i = +1 } },

	// Close
	{ MODKEY,             XK_Escape,      killclient,     {0} },


	// top row


	// Last workspace
	{ Mod4Mask,                       XK_Tab,    view,           {0} },

	// Alt tab
	{ Mod1Mask,                     XK_Tab,    altTabStart,         {0} },
	// switch master and stack with alt shift tab
	{ Mod1Mask|ShiftMask,             		XK_Tab,    movestack,	   {+1} },


	// mid row


	// show open windows
	{ MODKEY,                       XK_a,      spawn,          {.v = aroficmd } },

	// monitor control, focus then move
	{ MODKEY,                       XK_s,     focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_d,     focusmon,       {.i = +1 } },
	{ MODKEY|ControlMask,           XK_s,      tagmon,         {.i = -1 } },
	{ MODKEY|ControlMask,           XK_d,      tagmon,         {.i = +1 } },


	// Fullscreen and toggle float
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_f,  togglefloating, {0} },


	// bot row

	{ MODKEY,                       XK_m,      togglebar,      {0} },

	// changing size of master window on master and stack
	{ MODKEY,                       XK_z,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_x,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_c,      incnmaster,       {.i = +1} },


	// special/mod key row


	// rofi
	{ MODKEY,                       XK_Return,      spawn,          {.v = roficmd } },
	// no clue lol
	{ MODKEY|ShiftMask,             XK_Return, zoom,          {0} },

	// terminal
	{ MODKEY,                      XK_BackSpace, spawn,          {.v = termcmd } },


	// Scratchpads
	{ Mod1Mask,            			XK_q,  	   togglescratch,  {.ui = 0 } },
	{ Mod1Mask,            			XK_w,  	   togglescratch,  {.ui = 1 } },
	{ Mod1Mask,         	        XK_d,  	   togglescratch,  {.ui = 2 } },
	{ Mod1Mask,            			XK_s,  	   togglescratch,  {.ui = 3 } },
	{ Mod1Mask,            			XK_e,  	   togglescratch,  {.ui = 4 } },

	// workspace keys
	TAGKEYS(                        XK_q,                      0)
	TAGKEYS(                        XK_w,                      1)
	TAGKEYS(                        XK_e,                      2)
	TAGKEYS(                        XK_r,                      3)
	TAGKEYS(                        XK_t,                      4)
	TAGKEYS(                        XK_1,                      5)
	TAGKEYS(                        XK_2,                      6)
	TAGKEYS(                        XK_3,                      7)
	TAGKEYS(                        XK_4,                      8)
	TAGKEYS(                        XK_5,                      9)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

