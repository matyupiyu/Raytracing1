#include <stdlib.h>
#include "struct_vec.h"
#include "made_object_camera.h"
#include "intersection.h"
#ifndef SERCH_LIGHT_RANDOM_D_H // 二重読み込み防止（おまじない）
#define SERCH_LIGHT_RANDOM_D_H

// 交点からランダムな方向に反射するベクトルを生成
static inline Vec generate_random_d(Vec o, Vec normal){
    normal = normalize(normal);
    Vec dx = normal; // 法線方向の座標軸をdxとする
    Vec dy;

    if ((normal.x) > -0.9 && (normal.x) < 0.9){
        Vec x = {1.0, 0.0, 0.0};
        dy = normalize(cross(normal, x));
    } else {
        Vec x = {0.0, 1.0, 0.0};
        dy = normalize(cross(normal, x));
    }
    Vec dz = normalize(cross(dx, dy));

    Vec xyz = {0, 0, 0};

    while(1){
        double ux = 2 * ((double)rand() / RAND_MAX) - 1;
        double uy = 2 * ((double)rand() / RAND_MAX) - 1;
        double uz = 2 * ((double)rand() / RAND_MAX) - 1;

        if (ux < 0){
            ux = -ux;
        }

        Vec r = add(mul(dx, ux), add(mul(dy, uy), mul(dz, uz)));

        if (len(r) > 1.0){// 単位球の外ならやり直し
            continue;
        }

        xyz = normalize(r); // 単位ベクトル化
        break;
    }
    return xyz;
}


// その地点から光源が見えるかを判定し、光を計算
static inline Vec search_light(Vec normal, Vec o, Vec obj_col){
    Vec direct_lightning = {0.0, 0.0, 0.0}; // 光の初期化
    for (int i = 0; i < MAX_OBJECTS; i++){
        if (scene[i].type == LIGHT){ // 物体リストから光源を探す
            Vec light_pos = scene[i].li.o; //光源の位置
            Vec light_d = sub(light_pos, o); //光源の方向
            double distance = len(light_d); //光源の距離
            Vec light_n = normalize(light_d); //光源の方向の単位ベクトル

             //面の法線ベクトルと光線の方向ベクトルの単位ベクトル同士の内積はそのままcosΘ
            double cos_theta = dot(normal, light_n);
            // cos<0の場合、光が裏側から当たってるのでノーカウント
            if (cos_theta <= 0) continue; 
            int shadowed = 0; //光源が遮られない状態0に初期化
            for (int j = 0; j < MAX_OBJECTS; j++){
                // 自分自身, 光源との判定はスキップ
                if (i==j || scene[j].type == LIGHT) continue;

                // 当たり判定
                Hitrecord h = intersect_function(o, light_n, scene[j], j);
                // 何かに当たったら影
                if (h.t > 0.001 && h.t < distance){
                    shadowed = 1;
                    break;
                }
            }
            if (!shadowed){ // 当たらなかったら光を加算
                Vec light_color = hadamard(scene[i].col, obj_col);
                direct_lightning = add(direct_lightning, mul(light_color, cos_theta));
            }
        }
    }
    return direct_lightning;
}


#endif