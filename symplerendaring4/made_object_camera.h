#include "struct_vec.h"
#ifndef MADE_OBJECT_CAMERA_H  // 二重読み込み防止（おまじない）
#define MADE_OBJECT_CAMERA_H
#define MAX_OBJECTS 6 

// 構造体Cameraにより構成されたcamをつくる
static Camera cam = {
    {0 ,0, -5.0},  // camの位置ベクトル
    {0 ,0 , 1},    // カメラの方向ベクトル
    512, 512,      // camの解像度
    {0, 0, 0}      // screenの位置ベクトル   
};

// 物体をstruct_vec.hに応じてsceneで定義する
static Object scene[MAX_OBJECTS];

// C言語では、関数の外で"代入"を行うことができないそのため、関数scene
// にまとめてその中でscene[0].type=...のような代入を行う
static void scene_objects() {
    // まずは番号0の球を定義
    scene[0].type = SPHERE;
    scene[0].col = (Vec){0.78, 0, 0};
    scene[0].mat = SOLID;
    scene[0].s = (Sphere){{0, -0.5, 7.0}, 1.0};

    //次に番号1の無限平面を定義
    scene[1].type = INFPLANE;
    scene[1].col = (Vec){0.59, 0.59, 0.59};         
    scene[1].i.o = (Vec){0, -0.8, 0}; //平面上の任意の点(ここでは[0]と交わる点)
    scene[1].i.n = (Vec){0, 1, 0}; // 法線ベクトル
    
    // 2番の球
    scene[2].type = SPHERE;
    scene[2].col = (Vec){0, 0, 0.78};
    scene[2].mat = SOLID;
    scene[2].s = (Sphere){{0.2, -0.4, 1.0}, 0.53};

    // 番号3の円柱を定義
    scene[3].type = CYLINDER;
    scene[3].col = (Vec){0, 1.0, 0}; // 緑色
    scene[3].c.o = (Vec){0.6, -0.8, -0.5}; // 底面の中心
    scene[3].c.n = (Vec){0, 1, 0}; // 真上方向のベクトル
    scene[3].c.r = 0.25; // 半径
    scene[3].c.h = 0.2; // 高さ
    scene[3].mat = SOLID;
    
    // 番号4の有限平面を定義
    scene[4].type = LIMITPLANE;
    scene[4].col = (Vec){0, 0.78,0.78};
    scene[4].l.o = (Vec){-1.5, 0, 5};
    scene[4].l.n = (Vec){-0.6, -0.6, -1};
    scene[4].l.w_vec = (Vec){-1, 1, 0};
    scene[4].l.width = 1.2;
    scene[4].l.height = 1.5;
    scene[4].mat = SOLID;

    // 光源
    scene[5].type = LIGHT;
    scene[5].col = (Vec){0.9, 0.9, 0.9};
    scene[5].li.o = (Vec){-50, 50, -50};
};


#endif