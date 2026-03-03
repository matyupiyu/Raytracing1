#include <stdio.h>
#include <math.h>
#include "struct_vec.h"
#include "made_object_camera.h"
#include "intersection.h"
#include "intersectionpoint.h"

int main (){
    scene_objects();

    //ppmファイルを開く
    FILE *fp = fopen("image.ppm", "w");
    // ファイルが開けなかったらプログラムを終了する
    if (fp == NULL) return 1;
    // テキスト形式、512×512, 色の最大値255
    fprintf(fp, "P3\n%d %d\n255\n", cam.width, cam.height);


    for (int y = 0; y < cam.height; y++){
        for (int x = 0; x < cam.width; x++){
            // ピクセル上の座標0~511を三次元座標-1.0~1.0に合わせる
            double px = ((double)x / cam.width) * 2.0 - 1.0;
            //本来下から上だが、ここでマイナスをつけることにより、yを増やすと下から上になる
            double py = -(((double)y / cam.height) * 2.0 - 1.0); 
            
            // 光線の物体に対する当たり判定
            // カメラから各ピクセルに向かうベクトル
            Vec ray = normalize(sub((Vec){px, py, cam.screen.z}, cam.o));

            double min_t = 1e10;
            Vec sum_color = {0 ,0 ,0}; // そうサンプル色
            Vec avg_color = {0, 0, 0}; // 平均色
            int eightbit_color_r = 0; // 8bit色
            int eightbit_color_g = 0;
            int eightbit_color_b = 0;
            int samples = 100; // サンプル数
            int reflects = 1; // 反射回数

            // サンプリングの繰り返し
            for (int i=0; i < samples; i++){
                Vec ray_d = ray; // 現在のレイの方向
                Vec ray_o = cam.o; // 現在のレイの始点
                Vec throughput = {1.0, 1.0, 1.0}; // 光の減衰率
                Vec path_color = {0, 0, 0}; // 最終的なピクセルの光

                // 反射の繰り返し
                for (int j=0; j <= reflects; j++){
                    
                    Hitrecord best_hit = {1e30,-1}; // 最も近いヒット情報を巨大値で初期化

                    for (int k=0; k < MAX_OBJECTS; k++){
                        Hitrecord h = intersect_function(ray_o, ray_d, scene[k], k); // 全物体との交差判定
                    
                        if (h.scene_id!=-1 && h.t < best_hit.t){
                            best_hit = h; // より近い交点を保存
                        }
                    }

                    if (best_hit.scene_id != -1){ // 何かに当たった場合
                        Object obj = scene[best_hit.scene_id];
                        
                        if (obj.type == LIGHT){ // 光源に当たった場合
                            path_color = add(path_color, hadamard(throughput, obj.col));
                            break;
                        }
                        if (obj.mat == METAL){ // 金属に当たった場合
                            // SurfaceResult res = {}; // 鏡面反射予定
                        } else if (obj.mat == GLASS){ // ガラスに当たった場合
                            // SurfaceResult res = {}; // 屈折、全反射予定
                        } else { // 物体に当たった場合
                            SurfaceResult res = intersect_point(ray_o, ray_d, best_hit.t, obj);
                            throughput = hadamard(throughput, obj.col); // 次の物体のために減衰率をアダマールで積算
                            path_color = add(path_color, hadamard(throughput, res.color)); // イチサンプルとしてのピクセルの色
                            // 次のレイを生成
                            ray_o = res.next_o; // レイの方向をresの結果に更新
                            ray_d = res.next_d; // レイの方向をresの結果に更新
                        }
                    }
                }
            sum_color = add(sum_color, path_color); // サンプル色を累積
            }
        avg_color = mul(sum_color, 1.0 / samples); // 5は試行回数
        eightbit_color_r = round(fmax(0.0, fmin(1.0, avg_color.x)) * 255);// 1~0に収めて、8bit化して四捨五入で整数に丸める
        eightbit_color_g = round(fmax(0.0, fmin(1.0, avg_color.y)) * 255);
        eightbit_color_b = round(fmax(0.0, fmin(1.0, avg_color.z)) * 255);
        
        fprintf(fp, "%d %d %d\n", eightbit_color_r, eightbit_color_g, eightbit_color_b); // 画素ファイルに書き込み
        }
    }
}