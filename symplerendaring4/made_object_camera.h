#include "struct_vec.h"
#ifndef MADE_OBJECT_CAMERA_H  // 二重読み込み防止（おまじない）
#define MADE_OBJECT_CAMERA_H
#define MAX_OBJECTS 8

// 構造体Cameraの設定（視点を少し引いて全体が見えるように調整）
static Camera cam = {
    {0, 0, -5.0},  // 位置を少し後ろに
    {0, 0, 1},      // 前方を向く
    512, 512,
    {0, 0, 0}
};

static Object scene[MAX_OBJECTS];

static void scene_objects() {
    // --- 壁の設定 ---

    // 床 (白色)
    scene[0].type = INFPLANE;
    scene[0].col = (Vec){1, 1, 1};
    scene[0].i.o = (Vec){0, -1.0, 0};
    scene[0].i.n = (Vec){0, 1, 0};

    // 天井 (白色)
    scene[1].type = INFPLANE;
    scene[1].col = (Vec){1, 1, 1};
    scene[1].i.o = (Vec){0, 1.0, 0};
    scene[1].i.n = (Vec){0, 1, 0};

    // 奥の壁 (白色)
    scene[2].type = INFPLANE;
    scene[2].col = (Vec){1, 1, 0};
    scene[2].i.o = (Vec){0, 0, 2.0};
    scene[2].i.n = (Vec){0, 0, -1};

    // 右の壁 (緑色)
    scene[3].type = INFPLANE;
    scene[3].col = (Vec){0.1, 0.8, 0.1};
    scene[3].i.o = (Vec){1.0, 0, 0};
    scene[3].i.n = (Vec){-1, 0, 0};

    // 左の壁 (赤色)
    scene[4].type = INFPLANE;
    scene[4].col = (Vec){1.0, 0.1, 0.1};
    scene[4].i.o = (Vec){-1.0, 0, 0};
    scene[4].i.n = (Vec){1, 0, 0};

    // --- オブジェクト ---

    // 中央の球体
    scene[5].type = SPHERE;
    scene[5].col = (Vec){0, 0, 0.9}; // ほぼ白
    scene[5].mat = SOLID;
    scene[5].s = (Sphere){{0, -0.82, 1.0}, 0.18};

    // --- 光源 ---
    // 天井付近に配置
    scene[6].type = LIGHT;
    scene[6].col = (Vec){0.6, 0.6, 0.6}; // 少し強めに
    scene[6].li.o = (Vec){0, 0.95, 1.0};

    // 中央の球体
    scene[7].type = SPHERE;
    scene[7].col = (Vec){1.0, 1.0, 1.0}; // ほぼ白
    scene[7].mat = METAL;
    scene[7].s = (Sphere){{0.4, -0.75, 1.4}, 0.25};
}


#endif