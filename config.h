/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 20;        /* gaps between windows */
static const unsigned int snap      = 5;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "SourceCodePro-Regular:size=10" };
static const char dmenufont[]       = "SourceCodePro-Regular:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#222222";
static const char col_cyan[]        = "#e4f533";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
/*	{ "Brave",    NULL,       NULL,       1 << 8,       0,           -1 }, */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", "black", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *brave[]  = { "firefox", NULL };
static const char *pulsemixer[]  = { "st","-e", "pulsemixer" };
static const char *virt_manager[]  = { "virt-manager", NULL };
static const char *editor[]  = { "emacsclient", "--create-frame", NULL };
static const char *nnn[]  = { "st", "-e", "nnn" };
static const char *tor[]  = { "torbrowser-launcher", NULL };
static const char *qbittorrent[]  = { "qbittorrent", NULL };
static const char *ncmpcpp[] = { "st", "ncmpcpp", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = brave } },
	{ MODKEY,                       XK_v,      spawn,          {.v = virt_manager } },
	{ MODKEY,                       XK_z,      spawn,          {.v = nnn } },
	{ MODKEY,                       XK_e,      spawn,          {.v = editor } },
	{ MODKEY,                       XK_a,      spawn,          {.v = tor } },
	{ MODKEY,                       XK_x,      spawn,          {.v = qbittorrent } },
	{ MODKEY,                       XK_s,      spawn,          {.v = ncmpcpp } },
	{ MODKEY,                       XK_p,      spawn,          SHCMD("redshift -x")  },
	{ MODKEY,                       XK_o,      spawn,          SHCMD("redshift -O 4000K")  },
	{ MODKEY|ShiftMask,             XK_F9,     spawn,          SHCMD("mpc prev")  },
	{ MODKEY|ShiftMask,             XK_F10,    spawn,          SHCMD("mpc pause")  },
	{ MODKEY|ShiftMask,             XK_F11,    spawn,          SHCMD("mpc play")  },
	{ MODKEY|ShiftMask,             XK_F12,    spawn,          SHCMD("mpc next")  },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_k,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_u,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_k,      focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_h,  	   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_l,      tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ MODKEY,                       XK_F1,     spawn,          SHCMD("systemctl suspend")  },
	{ MODKEY,                       XK_F2,     spawn,          SHCMD("slock")  },
	{ MODKEY,                       XK_F3,     spawn,          SHCMD("reboot")  },
	{ MODKEY,                       XK_F4,     spawn,          SHCMD("shutdown now")  },
	{ MODKEY,                       XK_F5,     spawn,          SHCMD("xbacklight -set 0")  },
	{ MODKEY,                       XK_F6,     spawn,          SHCMD("xbacklight -dec 5")  },
	{ MODKEY,                       XK_F7,     spawn,          SHCMD("xbacklight -inc 5")  },
	{ MODKEY,                       XK_F8,     spawn,          SHCMD("xbacklight -set 100")  },
	{ MODKEY,                       XK_F9,     spawn,          SHCMD("pamixer -t")  },
	{ MODKEY,                       XK_F10,    spawn,          SHCMD("pamixer -d 5")  },
	{ MODKEY,                       XK_F11,    spawn,          SHCMD("pamixer -i 5")  },
	{ MODKEY,                       XK_F12,    spawn,          {.v = pulsemixer } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_Escape,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
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

