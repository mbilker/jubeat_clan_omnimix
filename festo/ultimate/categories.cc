#define LOG_MODULE "ultimate::categories"

#include "categories.h"
#include "music_db.h"

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

enum custom_sort_id : uint32_t {
    SORT_CUSTOM_ULTIMATE = SORT_DEFAULT_MAX_ID,
    SORT_CUSTOM_OMNIMIX,
    SORT_CUSTOM_JUBEAT_PLUS,
    // SORT_CUSTOM_JUBEAT_2020,
    SORT_CUSTOM_JUKEBEAT,
    SORT_CUSTOM_WESTERN,

    // T9
    SORT_CUSTOM_ABC,
    SORT_CUSTOM_DEF,
    SORT_CUSTOM_GHI,
    SORT_CUSTOM_JKL,
    SORT_CUSTOM_MNO,
    SORT_CUSTOM_PQRS,
    SORT_CUSTOM_TUV,
    SORT_CUSTOM_WXYZ,
    SORT_CUSTOM_0_9,

    SORT_CUSTOM_A,
    SORT_CUSTOM_B,
    SORT_CUSTOM_C,
    SORT_CUSTOM_D,
    SORT_CUSTOM_E,
    SORT_CUSTOM_F,
    SORT_CUSTOM_G,
    SORT_CUSTOM_H,
    SORT_CUSTOM_I,
    SORT_CUSTOM_J,
    SORT_CUSTOM_K,
    SORT_CUSTOM_L,
    SORT_CUSTOM_M,
    SORT_CUSTOM_N,
    SORT_CUSTOM_O,
    SORT_CUSTOM_P,
    SORT_CUSTOM_Q,
    SORT_CUSTOM_R,
    SORT_CUSTOM_S,
    SORT_CUSTOM_T,
    SORT_CUSTOM_U,
    SORT_CUSTOM_V,
    SORT_CUSTOM_W,
    SORT_CUSTOM_X,
    SORT_CUSTOM_Y,
    SORT_CUSTOM_Z,
};

static bool __cdecl custom_filter_omnimix(unsigned music_id, int diff, uint8_t level)
{
    music_db_entry_t *music = music_from_id(music_id);

    return music->ultimate_list_omnimix;
}

static bool __cdecl custom_filter_jubeat_plus(unsigned music_id, int diff, uint8_t level)
{
    music_db_entry_t *music = music_from_id(music_id);

    return music->ultimate_list_jubeat_plus;
}

// static bool __cdecl custom_filter_jubeat_2020(unsigned music_id, int diff, uint8_t level) {
//     music_db_entry_t *music = music_from_id(music_id);

//     return music->ultimate_list_jubeat_2020;
// }

static bool __cdecl custom_filter_jukebeat(unsigned music_id, int diff, uint8_t level)
{
    music_db_entry_t *music = music_from_id(music_id);

    return music->ultimate_list_jukebeat;
}

static bool __cdecl custom_filter_western(unsigned music_id, int diff, uint8_t level)
{
    music_db_entry_t *music = music_from_id(music_id);

    return music->ultimate_list_jukebeat || music->ultimate_list_western;
}

static bool __cdecl custom_filter_0_9(unsigned music_id, int diff, uint8_t level)
{
    music_db_entry_t *music = music_from_id(music_id);
    return music->sort_name[0] >= '0' && music->sort_name[0] <= '9';
}

#define MAKE_ALPHABET_SORTER(letter, chr)                                                          \
    static bool __cdecl custom_filter_##letter(unsigned music_id, int diff, uint8_t level)         \
    {                                                                                              \
        music_db_entry_t *music = music_from_id(music_id);                                         \
        return music->sort_name[0] == chr;                                                         \
    }

MAKE_ALPHABET_SORTER(a, 'a')
MAKE_ALPHABET_SORTER(b, 'b')
MAKE_ALPHABET_SORTER(c, 'c')
MAKE_ALPHABET_SORTER(d, 'd')
MAKE_ALPHABET_SORTER(e, 'e')
MAKE_ALPHABET_SORTER(f, 'f')
MAKE_ALPHABET_SORTER(g, 'g')
MAKE_ALPHABET_SORTER(h, 'h')
MAKE_ALPHABET_SORTER(i, 'i')
MAKE_ALPHABET_SORTER(j, 'j')
MAKE_ALPHABET_SORTER(k, 'k')
MAKE_ALPHABET_SORTER(l, 'l')
MAKE_ALPHABET_SORTER(m, 'm')
MAKE_ALPHABET_SORTER(n, 'n')
MAKE_ALPHABET_SORTER(o, 'o')
MAKE_ALPHABET_SORTER(p, 'p')
MAKE_ALPHABET_SORTER(q, 'q')
MAKE_ALPHABET_SORTER(r, 'r')
MAKE_ALPHABET_SORTER(s, 's')
MAKE_ALPHABET_SORTER(t, 't')
MAKE_ALPHABET_SORTER(u, 'u')
MAKE_ALPHABET_SORTER(v, 'v')
MAKE_ALPHABET_SORTER(w, 'w')
MAKE_ALPHABET_SORTER(x, 'x')
MAKE_ALPHABET_SORTER(y, 'y')
MAKE_ALPHABET_SORTER(z, 'z')

// clang-format off
const std::vector<category_hierarchy_t> extra_category_hierarchy = {
    {SORT_CUSTOM_ULTIMATE,    SORT_ROOT,            NULL,                      "UL_ROOT.png", NULL, NULL},
    {SORT_CUSTOM_OMNIMIX,     SORT_CUSTOM_ULTIMATE, custom_filter_omnimix,     "UL_SORT_GAME_OMNI.png", NULL, NULL},
    {SORT_CUSTOM_JUBEAT_PLUS, SORT_CUSTOM_ULTIMATE, custom_filter_jubeat_plus, "UL_SORT_GAME_JBPLUS.png", NULL, NULL},
    // {SORT_CUSTOM_JUBEAT_2020, SORT_CUSTOM_ULTIMATE, custom_filter_jubeat_2020, "UL_SORT_GAME_JB2020.png", NULL, NULL},
    {SORT_CUSTOM_JUKEBEAT,    SORT_CUSTOM_ULTIMATE, custom_filter_jukebeat,    "UL_SORT_GAME_JUKEBEAT.png", NULL, NULL},
    {SORT_CUSTOM_WESTERN,     SORT_CUSTOM_ULTIMATE, custom_filter_western,     "UL_SORT_WESTERN.png", NULL, NULL},
    {SORT_CUSTOM_ABC,         SORT_CATEGORY_NAME,   NULL,                      "UL_SORT_T9_ABC.png", NULL, NULL},
    {SORT_CUSTOM_DEF,         SORT_CATEGORY_NAME,   NULL,                      "UL_SORT_T9_DEF.png", NULL, NULL},
    {SORT_CUSTOM_GHI,         SORT_CATEGORY_NAME,   NULL,                      "UL_SORT_T9_GHI.png", NULL, NULL},
    {SORT_CUSTOM_JKL,         SORT_CATEGORY_NAME,   NULL,                      "UL_SORT_T9_JKL.png", NULL, NULL},
    {SORT_CUSTOM_MNO,         SORT_CATEGORY_NAME,   NULL,                      "UL_SORT_T9_MNO.png", NULL, NULL},
    {SORT_CUSTOM_PQRS,        SORT_CATEGORY_NAME,   NULL,                      "UL_SORT_T9_PQRS.png", NULL, NULL},
    {SORT_CUSTOM_TUV,         SORT_CATEGORY_NAME,   NULL,                      "UL_SORT_T9_TUV.png", NULL, NULL},
    {SORT_CUSTOM_WXYZ,        SORT_CATEGORY_NAME,   NULL,                      "UL_SORT_T9_WXYZ.png", NULL, NULL},
    {SORT_CUSTOM_0_9,         SORT_CATEGORY_NAME,   custom_filter_0_9,         "UL_SORT_T9_0_9.png", NULL, NULL},
    {SORT_CUSTOM_A,           SORT_CUSTOM_ABC,      custom_filter_a,           "UL_SORT_ALPHA_A.png", NULL, NULL},
    {SORT_CUSTOM_B,           SORT_CUSTOM_ABC,      custom_filter_b,           "UL_SORT_ALPHA_B.png", NULL, NULL},
    {SORT_CUSTOM_C,           SORT_CUSTOM_ABC,      custom_filter_c,           "UL_SORT_ALPHA_C.png", NULL, NULL},
    {SORT_CUSTOM_D,           SORT_CUSTOM_DEF,      custom_filter_d,           "UL_SORT_ALPHA_D.png", NULL, NULL},
    {SORT_CUSTOM_E,           SORT_CUSTOM_DEF,      custom_filter_e,           "UL_SORT_ALPHA_E.png", NULL, NULL},
    {SORT_CUSTOM_F,           SORT_CUSTOM_DEF,      custom_filter_f,           "UL_SORT_ALPHA_F.png", NULL, NULL},
    {SORT_CUSTOM_G,           SORT_CUSTOM_GHI,      custom_filter_g,           "UL_SORT_ALPHA_G.png", NULL, NULL},
    {SORT_CUSTOM_H,           SORT_CUSTOM_GHI,      custom_filter_h,           "UL_SORT_ALPHA_H.png", NULL, NULL},
    {SORT_CUSTOM_I,           SORT_CUSTOM_GHI,      custom_filter_i,           "UL_SORT_ALPHA_I.png", NULL, NULL},
    {SORT_CUSTOM_J,           SORT_CUSTOM_JKL,      custom_filter_j,           "UL_SORT_ALPHA_J.png", NULL, NULL},
    {SORT_CUSTOM_K,           SORT_CUSTOM_JKL,      custom_filter_k,           "UL_SORT_ALPHA_K.png", NULL, NULL},
    {SORT_CUSTOM_L,           SORT_CUSTOM_JKL,      custom_filter_l,           "UL_SORT_ALPHA_L.png", NULL, NULL},
    {SORT_CUSTOM_M,           SORT_CUSTOM_MNO,      custom_filter_m,           "UL_SORT_ALPHA_M.png", NULL, NULL},
    {SORT_CUSTOM_N,           SORT_CUSTOM_MNO,      custom_filter_n,           "UL_SORT_ALPHA_N.png", NULL, NULL},
    {SORT_CUSTOM_O,           SORT_CUSTOM_MNO,      custom_filter_o,           "UL_SORT_ALPHA_O.png", NULL, NULL},
    {SORT_CUSTOM_P,           SORT_CUSTOM_PQRS,     custom_filter_p,           "UL_SORT_ALPHA_P.png", NULL, NULL},
    {SORT_CUSTOM_Q,           SORT_CUSTOM_PQRS,     custom_filter_q,           "UL_SORT_ALPHA_Q.png", NULL, NULL},
    {SORT_CUSTOM_R,           SORT_CUSTOM_PQRS,     custom_filter_r,           "UL_SORT_ALPHA_R.png", NULL, NULL},
    {SORT_CUSTOM_S,           SORT_CUSTOM_PQRS,     custom_filter_s,           "UL_SORT_ALPHA_S.png", NULL, NULL},
    {SORT_CUSTOM_T,           SORT_CUSTOM_TUV,      custom_filter_t,           "UL_SORT_ALPHA_T.png", NULL, NULL},
    {SORT_CUSTOM_U,           SORT_CUSTOM_TUV,      custom_filter_u,           "UL_SORT_ALPHA_U.png", NULL, NULL},
    {SORT_CUSTOM_V,           SORT_CUSTOM_TUV,      custom_filter_v,           "UL_SORT_ALPHA_V.png", NULL, NULL},
    {SORT_CUSTOM_W,           SORT_CUSTOM_WXYZ,     custom_filter_w,           "UL_SORT_ALPHA_W.png", NULL, NULL},
    {SORT_CUSTOM_X,           SORT_CUSTOM_WXYZ,     custom_filter_x,           "UL_SORT_ALPHA_X.png", NULL, NULL},
    {SORT_CUSTOM_Y,           SORT_CUSTOM_WXYZ,     custom_filter_y,           "UL_SORT_ALPHA_Y.png", NULL, NULL},
    {SORT_CUSTOM_Z,           SORT_CUSTOM_WXYZ,     custom_filter_z,           "UL_SORT_ALPHA_Z.png", NULL, NULL},
};

const std::vector<category_listing_t> extra_category_layout = {
    // totally new folder
    {SORT_CUSTOM_ULTIMATE, 3, {
        {}, // leave first column blank
        {SORT_NULL, SORT_CUSTOM_OMNIMIX, SORT_CUSTOM_JUBEAT_PLUS, /*SORT_CUSTOM_JUBEAT_2020*/},
        {SORT_NULL, SORT_CUSTOM_JUKEBEAT, SORT_CUSTOM_WESTERN},
    }},
    // Ultimate invalidates a lot of existing categories and adds our own.
    // Custom categories are prepended to the list, so we can totally replace
    // them by fully specifying it here
    {SORT_ROOT, 7, {
        // SORT_ROOT in SORT_ROOT is the "Select a category" icon
        {SORT_ROOT, SORT_CUSTOM_ULTIMATE, SORT_CUSTOM_WESTERN},
        {SORT_ALL, SORT_CATEGORY_VERSION, SORT_CATEGORY_GENRE},
        {SORT_CATEGORY_LEVEL, SORT_CATEGORY_NAME, SORT_CATEGORY_ARTIST},
        {SORT_TARGET_MUSIC, SORT_HOLD, SORT_FULLCOMBO_CHALLENGE},
        {SORT_CATEGORY_PERFORMANCE, SORT_MYBEST, SORT_YOU_MIGHT_LIKE},
        {SORT_THIS_WEEK_RECOMMENDED, SORT_NATIONAL_POPULAR, SORT_TUNE_RUN},
        {SORT_IS_NEW},
    }},
    {SORT_CATEGORY_VERSION, 5, {
        {SORT_NULL, SORT_VER_jubeat, SORT_VER_ripples},
        {SORT_VER_knit, SORT_VER_copious, SORT_VER_saucer},
        {SORT_VER_saucer_fulfill, SORT_VER_prop, SORT_VER_Qubell},
        {SORT_VER_clan, SORT_VER_festo, SORT_CUSTOM_JUKEBEAT},
        {/*SORT_CUSTOM_JUBEAT_2020,*/ SORT_CUSTOM_JUBEAT_PLUS},
    }},

    {SORT_CATEGORY_NAME, 7, {
        {SORT_NULL, SORT_CUSTOM_GHI, SORT_CUSTOM_PQRS},
        {SORT_CUSTOM_ABC, SORT_CUSTOM_JKL, SORT_CUSTOM_TUV},
        {SORT_CUSTOM_DEF, SORT_CUSTOM_MNO, SORT_CUSTOM_WXYZ},
        // this extra NULL lets you fit every letter on one screen
        {SORT_CUSTOM_0_9, SORT_JP_A, SORT_JP_KA},
        {SORT_JP_SA, SORT_JP_TA, SORT_JP_NA},
        {SORT_JP_HA, SORT_JP_MA, SORT_JP_YA},
        {SORT_JP_RA, SORT_JP_WA},
    }},

    // Each individual subfolder for the T9 keyboard is a clone of the original
    // name sort, just with the letters you selected expanded. Also, the
    // expanded letters do not overlap the button you pressed initially, which
    // instead doubles as a "back" button. These two design choices make it more
    // ergonomic to quickly move around if you change your mind.
    // The extra buttons appear below, preferably, or above the selected button.
    {SORT_CUSTOM_ABC, 7, {
        {SORT_NULL, SORT_CUSTOM_A, SORT_CUSTOM_PQRS},
        {SORT_CATEGORY_NAME, SORT_CUSTOM_B, SORT_CUSTOM_TUV},
        {SORT_CUSTOM_DEF, SORT_CUSTOM_C, SORT_CUSTOM_WXYZ},
        {SORT_CUSTOM_0_9, SORT_JP_A, SORT_JP_KA},
        {SORT_JP_SA, SORT_JP_TA, SORT_JP_NA},
        {SORT_JP_HA, SORT_JP_MA, SORT_JP_YA},
        {SORT_JP_RA, SORT_JP_WA},
    }},
    {SORT_CUSTOM_DEF, 7, {
        {SORT_NULL, SORT_CUSTOM_D, SORT_CUSTOM_PQRS},
        {SORT_CUSTOM_ABC, SORT_CUSTOM_E, SORT_CUSTOM_TUV},
        {SORT_CATEGORY_NAME, SORT_CUSTOM_F, SORT_CUSTOM_WXYZ},
        {SORT_CUSTOM_0_9, SORT_JP_A, SORT_JP_KA},
        {SORT_JP_SA, SORT_JP_TA, SORT_JP_NA},
        {SORT_JP_HA, SORT_JP_MA, SORT_JP_YA},
        {SORT_JP_RA, SORT_JP_WA},
    }},
    {SORT_CUSTOM_GHI, 7, {
        {SORT_NULL, SORT_CATEGORY_NAME, SORT_CUSTOM_G},
        {SORT_CUSTOM_ABC, SORT_CUSTOM_JKL, SORT_CUSTOM_H},
        {SORT_CUSTOM_DEF, SORT_CUSTOM_MNO, SORT_CUSTOM_I},
        {SORT_CUSTOM_0_9, SORT_JP_A, SORT_JP_KA},
        {SORT_JP_SA, SORT_JP_TA, SORT_JP_NA},
        {SORT_JP_HA, SORT_JP_MA, SORT_JP_YA},
        {SORT_JP_RA, SORT_JP_WA},
    }},
    {SORT_CUSTOM_JKL, 7, {
        {SORT_NULL, SORT_CUSTOM_GHI, SORT_CUSTOM_J},
        {SORT_CUSTOM_ABC, SORT_CATEGORY_NAME, SORT_CUSTOM_K},
        {SORT_CUSTOM_DEF, SORT_CUSTOM_MNO, SORT_CUSTOM_L},
        {SORT_CUSTOM_0_9, SORT_JP_A, SORT_JP_KA},
        {SORT_JP_SA, SORT_JP_TA, SORT_JP_NA},
        {SORT_JP_HA, SORT_JP_MA, SORT_JP_YA},
        {SORT_JP_RA, SORT_JP_WA},
    }},
    {SORT_CUSTOM_MNO, 7, {
        {SORT_NULL, SORT_CUSTOM_GHI, SORT_CUSTOM_M},
        {SORT_CUSTOM_ABC, SORT_CUSTOM_JKL, SORT_CUSTOM_N},
        {SORT_CUSTOM_DEF, SORT_CATEGORY_NAME, SORT_CUSTOM_O},
        {SORT_CUSTOM_0_9, SORT_JP_A, SORT_JP_KA},
        {SORT_JP_SA, SORT_JP_TA, SORT_JP_NA},
        {SORT_JP_HA, SORT_JP_MA, SORT_JP_YA},
        {SORT_JP_RA, SORT_JP_WA},
    }},
    {SORT_CUSTOM_PQRS, 7, {
        {SORT_NULL, SORT_CUSTOM_P, SORT_CATEGORY_NAME},
        {SORT_CUSTOM_ABC, SORT_CUSTOM_Q, SORT_CUSTOM_TUV},
        {SORT_CUSTOM_DEF, SORT_CUSTOM_R, SORT_CUSTOM_WXYZ},
        {SORT_CUSTOM_0_9, SORT_CUSTOM_S, SORT_JP_KA},
        {SORT_JP_SA, SORT_JP_TA, SORT_JP_NA},
        {SORT_JP_HA, SORT_JP_MA, SORT_JP_YA},
        {SORT_JP_RA, SORT_JP_WA},
    }},
    {SORT_CUSTOM_TUV, 7, {
        {SORT_NULL, SORT_CUSTOM_T, SORT_CUSTOM_PQRS},
        {SORT_CUSTOM_ABC, SORT_CUSTOM_U, SORT_CATEGORY_NAME},
        {SORT_CUSTOM_DEF, SORT_CUSTOM_V, SORT_CUSTOM_WXYZ},
        {SORT_CUSTOM_0_9, SORT_JP_A, SORT_JP_KA},
        {SORT_JP_SA, SORT_JP_TA, SORT_JP_NA},
        {SORT_JP_HA, SORT_JP_MA, SORT_JP_YA},
        {SORT_JP_RA, SORT_JP_WA},
    }},
    {SORT_CUSTOM_WXYZ, 7, {
        {SORT_NULL, SORT_CUSTOM_W, SORT_CUSTOM_PQRS},
        {SORT_CUSTOM_ABC, SORT_CUSTOM_X, SORT_CUSTOM_TUV},
        {SORT_CUSTOM_DEF, SORT_CUSTOM_Y, SORT_CATEGORY_NAME},
        {SORT_CUSTOM_0_9, SORT_CUSTOM_Z, SORT_JP_KA},
        {SORT_JP_SA, SORT_JP_TA, SORT_JP_NA},
        {SORT_JP_HA, SORT_JP_MA, SORT_JP_YA},
        {SORT_JP_RA, SORT_JP_WA},
    }},
};

enum custom_group_id: uint32_t {
    GROUP_CUSTOM_0_9 = GROUP_DEFAULT_MAX_ID,
    GROUP_CUSTOM_ABC,
    GROUP_CUSTOM_DEF,
    GROUP_CUSTOM_GHI,
    GROUP_CUSTOM_JKL,
    GROUP_CUSTOM_MNO,
    GROUP_CUSTOM_PQRS,
    GROUP_CUSTOM_TUV,
    GROUP_CUSTOM_WXYZ,

    GROUP_CUSTOM_OMNIMIX,
    GROUP_CUSTOM_JUBEAT_PLUS,
    GROUP_CUSTOM_JUBEAT_2020,
    GROUP_CUSTOM_JUKEBEAT,

    GROUP_CUSTOM_OTHER,
};

// Grouping in song select
const std::vector<grouping_textures_t> extra_group_textures = {
    {GROUP_CUSTOM_0_9, "UL_GROUP_T9_0_9.png", NULL, NULL},
    {GROUP_CUSTOM_ABC, "UL_GROUP_T9_ABC.png", NULL, NULL},
    {GROUP_CUSTOM_DEF, "UL_GROUP_T9_DEF.png", NULL, NULL},
    {GROUP_CUSTOM_GHI, "UL_GROUP_T9_GHI.png", NULL, NULL},
    {GROUP_CUSTOM_JKL, "UL_GROUP_T9_JKL.png", NULL, NULL},
    {GROUP_CUSTOM_MNO, "UL_GROUP_T9_MNO.png", NULL, NULL},
    {GROUP_CUSTOM_PQRS, "UL_GROUP_T9_PQRS.png", NULL, NULL},
    {GROUP_CUSTOM_TUV, "UL_GROUP_T9_TUV.png", NULL, NULL},
    {GROUP_CUSTOM_WXYZ, "UL_GROUP_T9_WXYZ.png", NULL, NULL},

    {GROUP_CUSTOM_OMNIMIX, "UL_GROUP_GAME_OMNIMIX.png", NULL, NULL},
    {GROUP_CUSTOM_JUBEAT_PLUS, "UL_GROUP_GAME_JB_PLUS.png", NULL, NULL},
    {GROUP_CUSTOM_JUBEAT_2020, "UL_GROUP_GAME_JB_2020.png", NULL, NULL},
    {GROUP_CUSTOM_JUKEBEAT, "UL_GROUP_GAME_JUKEBEAT.png", NULL, NULL},

    {GROUP_CUSTOM_OTHER, "UL_GROUP_OTHER.png", NULL, NULL},
};

const std::vector<hierarchy_texture_t> extra_hierarchy_textures = {
    // defaults
    {SORT_ROOT,                     SORT_NULL,                 0, nullptr},
    {SORT_ALL,                      SORT_ROOT,                 2, "smm_t8200"},
    {SORT_YOU_MIGHT_LIKE,           SORT_ROOT,                 2, "smm_t8890"},
    {SORT_CATEGORY_GENRE,           SORT_ROOT,                 1, "smm_t8500"},
    {SORT_POPS,                     SORT_CATEGORY_GENRE,       2, "smm_t8516"},
    {SORT_ANIME,                    SORT_CATEGORY_GENRE,       2, "smm_t8512"},
    {SORT_SOCIAL_MUSIC,             SORT_CATEGORY_GENRE,       2, "smm_t8519"},
    {SORT_GAME,                     SORT_CATEGORY_GENRE,       2, "smm_t8517"},
    {SORT_CLASSIC,                  SORT_CATEGORY_GENRE,       2, "smm_t8518"},
    {SORT_ORIGINAL,                 SORT_CATEGORY_GENRE,       2, "smm_t8515"},
    {SORT_TOUHOU_ARRANGE,           SORT_CATEGORY_GENRE,       2, "smm_t8520"},
    {SORT_CATEGORY_LEVEL,           SORT_ROOT,                 1, "smm_t8400"},
    {SORT_LEVEL1,                   SORT_CATEGORY_LEVEL,       2, "smm_t8410"},
    {SORT_LEVEL2,                   SORT_CATEGORY_LEVEL,       2, "smm_t8411"},
    {SORT_LEVEL3,                   SORT_CATEGORY_LEVEL,       2, "smm_t8412"},
    {SORT_LEVEL4,                   SORT_CATEGORY_LEVEL,       2, "smm_t8413"},
    {SORT_LEVEL5,                   SORT_CATEGORY_LEVEL,       2, "smm_t8414"},
    {SORT_LEVEL6,                   SORT_CATEGORY_LEVEL,       2, "smm_t8415"},
    {SORT_LEVEL7,                   SORT_CATEGORY_LEVEL,       2, "smm_t8416"},
    {SORT_LEVEL8,                   SORT_CATEGORY_LEVEL,       2, "smm_t8417"},
    {SORT_LEVEL9,                   SORT_CATEGORY_LEVEL,       2, "smm_t8418"},
    {SORT_LEVEL10,                  SORT_CATEGORY_LEVEL,       2, "smm_t8419"},
    {SORT_CATEGORY_NAME,            SORT_ROOT,                 1, "smm_t8300"},
    {SORT_JP_A,                     SORT_CATEGORY_NAME,        2, "smm_t8310"},
    {SORT_JP_KA,                    SORT_CATEGORY_NAME,        2, "smm_t8311"},
    {SORT_JP_SA,                    SORT_CATEGORY_NAME,        2, "smm_t8312"},
    {SORT_JP_TA,                    SORT_CATEGORY_NAME,        2, "smm_t8313"},
    {SORT_JP_NA,                    SORT_CATEGORY_NAME,        2, "smm_t8314"},
    {SORT_JP_HA,                    SORT_CATEGORY_NAME,        2, "smm_t8315"},
    {SORT_JP_MA,                    SORT_CATEGORY_NAME,        2, "smm_t8316"},
    {SORT_JP_YA,                    SORT_CATEGORY_NAME,        2, "smm_t8317"},
    {SORT_JP_RA,                    SORT_CATEGORY_NAME,        2, "smm_t8318"},
    {SORT_JP_WA,                    SORT_CATEGORY_NAME,        2, "smm_t8319"},
    {SORT_HOLD,                     SORT_ROOT,                 2, "smm_t8860"},
    {SORT_IS_NEW,                   SORT_ROOT,                 2, "smm_t8114"},
    {SORT_NATIONAL_POPULAR,         SORT_ROOT,                 2, "smm_t8111"},
    {SORT_FULLCOMBO_CHALLENGE,      SORT_ROOT,                 2, "smm_t8600"},
    {SORT_CATEGORY_PERFORMANCE,     SORT_ROOT,                 1, "smm_t8700"},
    {SORT_UNPLAYED,                 SORT_CATEGORY_PERFORMANCE, 2, "smm_t8710"},
    {SORT_NOT_FULL_COMBO,           SORT_CATEGORY_PERFORMANCE, 2, "smm_t8720"},
    {SORT_HAS_FULL_COMBO,           SORT_CATEGORY_PERFORMANCE, 2, "smm_t8721"},
    {SORT_SOME_GRAY,                SORT_CATEGORY_PERFORMANCE, 2, "smm_t8730"},
    {SORT_NO_GRAY,                  SORT_CATEGORY_PERFORMANCE, 2, "smm_t8731"},
    {SORT_NOT_ALL_YELLOW,           SORT_CATEGORY_PERFORMANCE, 2, "smm_t8732"},
    {SORT_HAS_ALL_YELLOW,           SORT_CATEGORY_PERFORMANCE, 2, "smm_t8733"},
    {SORT_RANK_E,                   SORT_CATEGORY_PERFORMANCE, 2, "smm_t8740"},
    {SORT_RANK_D,                   SORT_CATEGORY_PERFORMANCE, 2, "smm_t8741"},
    {SORT_RANK_C,                   SORT_CATEGORY_PERFORMANCE, 2, "smm_t8742"},
    {SORT_RANK_B,                   SORT_CATEGORY_PERFORMANCE, 2, "smm_t8743"},
    {SORT_RANK_A,                   SORT_CATEGORY_PERFORMANCE, 2, "smm_t8744"},
    {SORT_RANK_S,                   SORT_CATEGORY_PERFORMANCE, 2, "smm_t8745"},
    {SORT_RANK_SS,                  SORT_CATEGORY_PERFORMANCE, 2, "smm_t8746"},
    {SORT_RANK_SSS,                 SORT_CATEGORY_PERFORMANCE, 2, "smm_t8747"},
    {SORT_RANK_EXC,                 SORT_CATEGORY_PERFORMANCE, 2, "smm_t8748"},
    {SORT_MYBEST,                   SORT_ROOT,                 2, "smm_t8113"},
    {SORT_CATEGORY_TOURNAMENT,      SORT_ROOT,                 1, "smm_t8800"},
    {SORT_TOURNAMENT_1,             SORT_CATEGORY_TOURNAMENT,  2, "smm_t8810"},
    {SORT_TOURNAMENT_2,             SORT_CATEGORY_TOURNAMENT,  2, "smm_t8810"},
    {SORT_TOURNAMENT_3,             SORT_CATEGORY_TOURNAMENT,  2, "smm_t8810"},
    {SORT_TOURNAMENT_4,             SORT_CATEGORY_TOURNAMENT,  2, "smm_t8810"},
    {SORT_TOURNAMENT_5,             SORT_CATEGORY_TOURNAMENT,  2, "smm_t8810"},
    {SORT_CATEGORY_JUBEAT_LAB,      SORT_ROOT,                 1, "smm_t8820"},
    {SORT_LAB_MY_LIST,              SORT_CATEGORY_JUBEAT_LAB,  2, "smm_t8830"},
    {SORT_LAB_DOWNLOAD_RANKING,     SORT_CATEGORY_JUBEAT_LAB,  2, "smm_t8832"},
    {SORT_LAB_PLAYCOUNT_RANKING,    SORT_CATEGORY_JUBEAT_LAB,  2, "smm_t8831"},
    {SORT_LAB_GOOD_CHART_RANKING,   SORT_CATEGORY_JUBEAT_LAB,  2, "smm_t8833"},
    {SORT_IS_WEEKLY_TARGET,         SORT_ROOT,                 2, "smm_t8116"},
    {SORT_CATEGORY_VERSION,         SORT_ROOT,                 1, "smm_t8420"},
    {SORT_VER_jubeat,               SORT_CATEGORY_VERSION,     2, "smm_t8430"},
    {SORT_VER_ripples,              SORT_CATEGORY_VERSION,     2, "smm_t8431"},
    {SORT_VER_knit,                 SORT_CATEGORY_VERSION,     2, "smm_t8432"},
    {SORT_VER_copious,              SORT_CATEGORY_VERSION,     2, "smm_t8433"},
    {SORT_VER_saucer,               SORT_CATEGORY_VERSION,     2, "smm_t8434"},
    {SORT_VER_saucer_fulfill,       SORT_CATEGORY_VERSION,     2, "smm_t8435"},
    {SORT_VER_prop,                 SORT_CATEGORY_VERSION,     2, "smm_t8436"},
    {SORT_VER_Qubell,               SORT_CATEGORY_VERSION,     2, "smm_t8437"},
    {SORT_VER_clan,                 SORT_CATEGORY_VERSION,     2, "smm_t8438"},
    {SORT_VER_festo,                SORT_CATEGORY_VERSION,     2, "smm_t8439"},
    {SORT_CATEGORY_ARTIST,          SORT_ROOT,                 1, "smm_t8320"},
    {SORT_ARTIST_Sota_Fujimori,     SORT_CATEGORY_ARTIST,      2, "smm_t8330"},
    {SORT_ARTIST_DJ_YOSHITAKA,      SORT_CATEGORY_ARTIST,      2, "smm_t8331"},
    {SORT_ARTIST_Nekomata_Master,   SORT_CATEGORY_ARTIST,      2, "smm_t8332"},
    {SORT_ARTIST_TAG,               SORT_CATEGORY_ARTIST,      2, "smm_t8333"},
    {SORT_ARTIST_wac,               SORT_CATEGORY_ARTIST,      2, "smm_t8334"},
    {SORT_ARTIST_LED,               SORT_CATEGORY_ARTIST,      2, "smm_t8335"},
    {SORT_ARTIST_Hinabita,          SORT_CATEGORY_ARTIST,      2, "smm_t8336"},
    {SORT_ARTIST_Akhuta,            SORT_CATEGORY_ARTIST,      2, "smm_t8337"},
    {SORT_ARTIST_Tomoaki_Hirono,    SORT_CATEGORY_ARTIST,      2, "smm_t8338"},
    {SORT_ARTIST_S_C_U,             SORT_CATEGORY_ARTIST,      2, "smm_t8339"},
    {SORT_ARTIST_Ryu,               SORT_CATEGORY_ARTIST,      2, "smm_t8340"},
    {SORT_ARTIST_kors_k,            SORT_CATEGORY_ARTIST,      2, "smm_t8341"},
    {SORT_ARTIST_dj_TAKA,           SORT_CATEGORY_ARTIST,      2, "smm_t8342"},
    {SORT_ARTIST_DJ_TOTTO,          SORT_CATEGORY_ARTIST,      2, "smm_t8343"},
    {SORT_ARTIST_Mutsuhiko_Izumi,   SORT_CATEGORY_ARTIST,      2, "smm_t8344"},
    {SORT_ARTIST_Yoshihiko_Koezuka, SORT_CATEGORY_ARTIST,      2, "smm_t8345"},
    {SORT_ARTIST_TOMOSUKE,          SORT_CATEGORY_ARTIST,      2, "smm_t8346"},
    {SORT_ARTIST_Asaki,             SORT_CATEGORY_ARTIST,      2, "smm_t8347"},
    {SORT_ARTIST_seiya_murai,       SORT_CATEGORY_ARTIST,      2, "smm_t8348"},
    {SORT_ARTIST_PON,               SORT_CATEGORY_ARTIST,      2, "smm_t8349"},
    {SORT_ARTIST_Qrispy_Joybox,     SORT_CATEGORY_ARTIST,      2, "smm_t8350"},
    {SORT_ARTIST_GUHROOVY,          SORT_CATEGORY_ARTIST,      2, "smm_t8351"},
    {SORT_ARTIST_U1_ASAMi,          SORT_CATEGORY_ARTIST,      2, "smm_t8352"},
    {SORT_ARTIST_Hommarju,          SORT_CATEGORY_ARTIST,      2, "smm_t8353"},
    {SORT_ARTIST_ARM,               SORT_CATEGORY_ARTIST,      2, "smm_t8354"},
    {SORT_ARTIST_AOP,               SORT_CATEGORY_ARTIST,      2, "smm_t8355"},
    {SORT_ARTIST_NEKOHIROKI,        SORT_CATEGORY_ARTIST,      2, "smm_t8356"},
    {SORT_ARTIST_Mayumi_Morinaga,   SORT_CATEGORY_ARTIST,      2, "smm_t8357"},
    {SORT_SHOP,                     SORT_ROOT,                 1, nullptr},
    {SORT_PJ_MATCH,                 SORT_ROOT,                 1, nullptr},
    {SORT_TUNE_RUN,                 SORT_ROOT,                 1, nullptr},
    {SORT_TUNE_RUN_1,               SORT_ROOT,                 1, nullptr},
    {SORT_TUNE_RUN_2,               SORT_ROOT,                 2, "smm_t8104"},
    {SORT_TARGET_MUSIC,             SORT_ROOT,                 2, "smm_t8840"},
    {SORT_THIS_WEEK_RECOMMENDED,    SORT_ROOT,                 2, "smm_t8105"},

    // ultimate
    // NOTE: 64 byte buffers used for {name}_ja.png expansion
    {SORT_CUSTOM_ULTIMATE,          SORT_ROOT,                 1, "ul_arch_ultimate"},
    {SORT_CUSTOM_OMNIMIX,           SORT_CUSTOM_ULTIMATE,      2, "ul_arch_omnimix"},
    {SORT_CUSTOM_JUBEAT_PLUS,       SORT_CUSTOM_ULTIMATE,      2, "ul_arch_jubeat_plus"},
    {SORT_CUSTOM_JUKEBEAT,          SORT_CUSTOM_ULTIMATE,      2, "ul_arch_jukebeat"},
    {SORT_CUSTOM_WESTERN,           SORT_CUSTOM_ULTIMATE,      2, "ul_arch_western"},
    {SORT_CUSTOM_ABC,               SORT_ROOT,                 1, nullptr},
    {SORT_CUSTOM_DEF,               SORT_ROOT,                 1, nullptr},
    {SORT_CUSTOM_GHI,               SORT_ROOT,                 1, nullptr},
    {SORT_CUSTOM_JKL,               SORT_ROOT,                 1, nullptr},
    {SORT_CUSTOM_MNO,               SORT_ROOT,                 1, nullptr},
    {SORT_CUSTOM_PQRS,              SORT_ROOT,                 1, nullptr},
    {SORT_CUSTOM_TUV,               SORT_ROOT,                 1, nullptr},
    {SORT_CUSTOM_WXYZ,              SORT_ROOT,                 1, nullptr},
    {SORT_CUSTOM_0_9,               SORT_CATEGORY_NAME,        2, "ul_arch_0_9"},
    {SORT_CUSTOM_A,                 SORT_CATEGORY_NAME,        2, "ul_arch_a"},
    {SORT_CUSTOM_B,                 SORT_CATEGORY_NAME,        2, "ul_arch_b"},
    {SORT_CUSTOM_C,                 SORT_CATEGORY_NAME,        2, "ul_arch_c"},
    {SORT_CUSTOM_D,                 SORT_CATEGORY_NAME,        2, "ul_arch_d"},
    {SORT_CUSTOM_E,                 SORT_CATEGORY_NAME,        2, "ul_arch_e"},
    {SORT_CUSTOM_F,                 SORT_CATEGORY_NAME,        2, "ul_arch_f"},
    {SORT_CUSTOM_G,                 SORT_CATEGORY_NAME,        2, "ul_arch_g"},
    {SORT_CUSTOM_H,                 SORT_CATEGORY_NAME,        2, "ul_arch_h"},
    {SORT_CUSTOM_I,                 SORT_CATEGORY_NAME,        2, "ul_arch_i"},
    {SORT_CUSTOM_J,                 SORT_CATEGORY_NAME,        2, "ul_arch_j"},
    {SORT_CUSTOM_K,                 SORT_CATEGORY_NAME,        2, "ul_arch_k"},
    {SORT_CUSTOM_L,                 SORT_CATEGORY_NAME,        2, "ul_arch_l"},
    {SORT_CUSTOM_M,                 SORT_CATEGORY_NAME,        2, "ul_arch_m"},
    {SORT_CUSTOM_N,                 SORT_CATEGORY_NAME,        2, "ul_arch_n"},
    {SORT_CUSTOM_O,                 SORT_CATEGORY_NAME,        2, "ul_arch_o"},
    {SORT_CUSTOM_P,                 SORT_CATEGORY_NAME,        2, "ul_arch_p"},
    {SORT_CUSTOM_Q,                 SORT_CATEGORY_NAME,        2, "ul_arch_q"},
    {SORT_CUSTOM_R,                 SORT_CATEGORY_NAME,        2, "ul_arch_r"},
    {SORT_CUSTOM_S,                 SORT_CATEGORY_NAME,        2, "ul_arch_s"},
    {SORT_CUSTOM_T,                 SORT_CATEGORY_NAME,        2, "ul_arch_t"},
    {SORT_CUSTOM_U,                 SORT_CATEGORY_NAME,        2, "ul_arch_u"},
    {SORT_CUSTOM_V,                 SORT_CATEGORY_NAME,        2, "ul_arch_v"},
    {SORT_CUSTOM_W,                 SORT_CATEGORY_NAME,        2, "ul_arch_w"},
    {SORT_CUSTOM_X,                 SORT_CATEGORY_NAME,        2, "ul_arch_x"},
    {SORT_CUSTOM_Y,                 SORT_CATEGORY_NAME,        2, "ul_arch_y"},
    {SORT_CUSTOM_Z,                 SORT_CATEGORY_NAME,        2, "ul_arch_z"},
};

// clang-format on

uint32_t __fastcall category_group_fn_alphabet(
    enum group_type group_type, const music_info_for_grouping_t *info)
{
    if (group_type != GROUP_TYPE_NAME || !info) {
        return GROUP_INVALID;
    }
    auto song = music_from_id(info->id);
    auto first = song->sort_name[0];

    if (first >= '0' && first <= '9') {
        return GROUP_CUSTOM_0_9;
    } else if (first >= 'a' && first <= 'c') {
        return GROUP_CUSTOM_ABC;
    } else if (first >= 'd' && first <= 'f') {
        return GROUP_CUSTOM_DEF;
    } else if (first >= 'g' && first <= 'i') {
        return GROUP_CUSTOM_GHI;
    } else if (first >= 'j' && first <= 'l') {
        return GROUP_CUSTOM_JKL;
    } else if (first >= 'm' && first <= 'o') {
        return GROUP_CUSTOM_MNO;
    } else if (first >= 'p' && first <= 's') {
        return GROUP_CUSTOM_PQRS;
    } else if (first >= 't' && first <= 'v') {
        return GROUP_CUSTOM_TUV;
    } else if (first >= 'w' && first <= 'z') {
        return GROUP_CUSTOM_WXYZ;
    }

    return GROUP_INVALID;
}

uint32_t __fastcall category_group_fn_genre_custom(
    enum group_type group_type, const music_info_for_grouping_t *info)
{
    if (group_type != GROUP_TYPE_GENRE || !info) {
        return GROUP_INVALID;
    }
    auto song = music_from_id(info->id);

    if (song->genre_pops == GENRE_PRIMARY) {
        return GROUP_POPS;
    } else if (song->genre_anime == GENRE_PRIMARY) {
        return GROUP_ANIME;
    } else if (song->genre_socialmusic == GENRE_PRIMARY) {
        return GROUP_SOCIAL_MUSIC;
    } else if (song->genre_toho == GENRE_PRIMARY) {
        return GROUP_TOUHOU_ARRANGE;
    } else if (song->genre_game == GENRE_PRIMARY) {
        return GROUP_GAME;
    } else if (song->genre_classical == GENRE_PRIMARY) {
        return GROUP_CLASSIC;
    } else if (song->genre_original == GENRE_PRIMARY) {
        return GROUP_ORIGINAL;
    } else {
        // only change: don't dump genre-less songs into Pops (2)
        return GROUP_CUSTOM_OTHER;
    }
}

uint32_t __fastcall category_group_fn_version_custom(
    enum group_type group_type, const music_info_for_grouping_t *info)
{
    if (group_type != GROUP_TYPE_VERSION || !info) {
        return GROUP_INVALID;
    }
    auto song = music_from_id(info->id);

    if (song->ultimate_list_omnimix) {
        // omni songs can just fall into their original version
        return GROUP_INVALID;
    } else if (song->ultimate_list_jubeat_plus) {
        return GROUP_CUSTOM_JUBEAT_PLUS;
    } else if (song->ultimate_list_jubeat_2020) {
        return GROUP_CUSTOM_JUBEAT_2020;
    } else if (song->ultimate_list_jukebeat) {
        return GROUP_CUSTOM_JUKEBEAT;
    }

    // fallback to normal handler
    return GROUP_INVALID;
}

// Compare functions used to sort the music display list - we add extra
// categories to version and genre, so we need to replicate them both

static int version_rank(int mid)
{
    auto song = music_from_id(mid);

    if (song->ultimate_list_jubeat_plus) {
        return 16;
    } else if (song->ultimate_list_jubeat_2020) {
        return 15;
    } else if (song->ultimate_list_jukebeat) {
        return 14;
        // copied from game
    } else if (music_db_is_exists_version_from_ver9(mid)) {
        return 13;
    } else if (music_db_is_exists_version_from_ver8(mid)) {
        return 12;
    } else if (music_db_is_exists_version_from_ver7(mid)) {
        return 11;
    } else if (music_db_is_exists_version_from_ver6(mid)) {
        return 10;
    } else if (music_db_is_exists_version_from_ver5_5(mid)) {
        return 9;
    } else if (music_db_is_exists_version_from_ver5(mid)) {
        return 8;
    } else if (music_db_is_exists_version_from_ver4(mid)) {
        return 6;
    } else if (music_db_is_exists_version_from_ver3(mid)) {
        return 4;
    } else if (music_db_is_exists_version_from_ver2(mid)) {
        return 2;
    } else {
        return 0;
    }
}

int __cdecl version_sorter(const music_info_for_grouping_t *a, const music_info_for_grouping_t *b)
{
    int a_rank = version_rank(a->id);
    int b_rank = version_rank(b->id);

    if (a_rank < b_rank) {
        return -1;
    } else if (a_rank > b_rank) {
        return 1;
    } else {
        return name_sorter(a, b);
    }
}

static int genre_rank(int mid)
{
    auto song = music_from_id(mid);
    // comparing to 2 (not just truthiness) is what the game does
    if (song->genre_pops == GENRE_PRIMARY) {
        return 1;
    } else if (song->genre_anime == GENRE_PRIMARY) {
        return 2;
    } else if (song->genre_socialmusic == GENRE_PRIMARY) {
        return 3;
    } else if (song->genre_toho == GENRE_PRIMARY) {
        return 4;
    } else if (song->genre_game == GENRE_PRIMARY) {
        return 5;
    } else if (song->genre_classical == GENRE_PRIMARY) {
        return 6;
    } else if (song->genre_original == GENRE_PRIMARY) {
        return 7;
    } else {
        // this is the only place we differ - fallback to "Other" at end of list
        return 8;
    }
}

int __cdecl genre_sorter(const music_info_for_grouping_t *a, const music_info_for_grouping_t *b)
{
    int a_rank = genre_rank(a->id);
    int b_rank = genre_rank(b->id);

    if (a_rank < b_rank) {
        return -1;
    } else if (a_rank > b_rank) {
        return 1;
    } else {
        return name_sorter(a, b);
    }
}
