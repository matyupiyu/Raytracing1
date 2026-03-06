#include "struct_vec.h"
#ifndef MADE_OBJECT_CAMERA_H  // 二重読み込み防止（おまじない）
#define MADE_OBJECT_CAMERA_H
#define MAX_OBJECTS 5

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

    // --- オブジェクト ---

    // 中央の球体
    scene[1].type = SPHERE;
    scene[1].col = (Vec){0, 0, 0.9}; 
    scene[1].mat = SOLID;
    scene[1].s = (Sphere){{0, -0.82, 1.0}, 0.18};

    // --- 光源 ---
    // 天井付近に配置
    scene[2].type = LIGHT;
    scene[2].col = (Vec){0.6, 0.6, 0.6}; // 少し強めに
    scene[2].li.o = (Vec){0, 0.95, 1.0};

    // 鏡面の球体
    scene[3].type = SPHERE;
    scene[3].col = (Vec){1.0, 1.0, 1.0}; // ほぼ白
    scene[3].mat = METAL;
    scene[3].s = (Sphere){{0.4, -0.75, 1.4}, 0.25};

    // 鏡面の球体
    scene[4].type = SPHERE;
    scene[4].col = (Vec){1.0, 0.84, 0}; // ほぼ白
    scene[4].mat = METAL;
    scene[4].s = (Sphere){{-0.4, -0.75, 1.4}, 0.25};
}


#endif