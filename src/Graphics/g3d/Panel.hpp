#pragma once

#include <memory>
#include "Graphics/glHeaders.hpp"
#include "Graphics/Rect.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/g3d/TexturedCompatible.hpp"
#include "Graphics/g3d/TexturedShader.hpp"

namespace Graphics {
  namespace g3d {
    /// テクスチャを貼っておける板
    /// デフォルトでは右手座標系においてZ軸正方向を表にして配置されている.
    /// 透明度を設定することもできる
    class Panel : public TexturedCompatible {
      protected:
        bool ownedTexture;
        Texture* texture;
        double alpha;
        glm::vec3 colorModulation;
        glm::vec2 realSize;

        GLuint vbo;
        GLuint ibo;
        GLuint iboSize;

        glm::mat4 scale;
        glm::mat4 trans;
        glm::mat4 rotate;

        /// @fn
        /// 派生クラス用のデフォルトコンストラクタ
        Panel();

        /// @fn
        /// 派生クラス用のシャローコピーコンストラクタ
        Panel(Panel&);

        /// @fn
        /// 共通の下準備
        /// 一番最初には準備しきれないので
        void commonConstructor(Texture* texture, GLfloat width, GLfloat height, Rect rect, GLfloat);
      public:
        static std::shared_ptr<TexturedShader> defaultShader;
        static void setupShader(std::string, std::string);
        static void setupShader(std::shared_ptr<TexturedShader> texturedShader);

        glm::vec2 getSize();

        /// @fn
        /// テクスチャを与えないで画像ファイルから直接生成します
        /// このテクスチャは自動開放されるのでそれ用のフラグを立てます
        /// あとはテクスチャを与える場合と同じです
        Panel(std::string path, GLfloat scale);

        /// @fn
        /// テクスチャのサイズから大きさを算出します.
        /// 一般に大きすぎるのでscaleで調整します.
        /// 
        /// @param (scale) 拡大縮小
        Panel(Texture* texture, GLfloat scale);

        /// @fn
        /// 幅と高さを指定したパネルを作成します
        /// テクスチャは全面に張り出されます
        Panel(Texture* texture, GLfloat width, GLfloat height);

        /// @fn
        /// 幅と高さを指定したパネルを作成します
        /// テクスチャは指定した矩形を切り抜いて全面に貼り付けます
        /// @param (uvrect) ピクセル単位の切り抜き矩形
        Panel(Texture* texture, GLfloat width, GLfloat height, Rect uvrect);
        /// @fn
        /// デストラクタ
        /// バッファを解放する
        ~Panel();

        /// @fn
        /// 透明度を設定する
        void setAlpha(double);

        /// @fn
        /// 色を加工する
        /// 
        /// @param (r) 0で何もしない. 正で色を足す. 負で色を引く.
        void setColorModulation(double r, double g, double b);

        /// @fn
        /// 位置を設定する
        void setPosition(GLfloat x, GLfloat y, GLfloat z);

        /// @fn
        /// 回転させる
        void setRotation(GLfloat radian, glm::vec3 axis);

        /// @fn
        /// デフォルトシェーダで描画する
        void renderWithDefault();

        // 純粋仮想関数たち
        GLuint getVBO();
        GLuint getIBO();
        GLuint getIBOsize();
        GLuint getTexture();
        glm::mat4 getModelMatrix();
        GLfloat getAlpha();
        glm::vec3 getColorModulation();
    };
      
  } // namespace g3d
} // namespace Graphics

