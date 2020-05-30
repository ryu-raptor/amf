# アリスのミュージックフライト

歌いながら空を飛ぶような音楽ゲーム

![slides](documents/alice_slides.pdf)

## ビルド
(注意) GitHub への移植作業がまだ完了していないため Windows, MacOSX でのビルドはできないかもしれません.

### 依存
Linux を基準にしている.
Windows は `src/lib/win` にライブラリ本体を, `src/include` にヘッダを入れて下さい.
MacOSX は `src/lib/macosx/Framework` にライブラリの Framework を入れて下さい.

- g++ または clang : C++14 をサポートするもの. Windows の場合は Cygwin 環境など.
- lodepng : git submodule で解決
- glew
- glfw : linux では `pkg-config` で `glfw3` が見つかるか確認して下さい.
- SFML : sfml-audio に依存. linux では `pkg-config` で `sfml-audio` が見つかるか確認して下さい.

ArchLinux での一例
```
% sudo pacman -S base-devel glew glfw-x11 sfml
```

### ビルド手順
Windows と MacOSX は make の `os` 変数をそれぞれ win, osx と指定.
無指定で Linux と仮定する.

下記は Windows の例

本体プログラム
```
% cd src
% make os=win
```

譜面エディタ
```
% cd src
% make os=win ChartEditor
```

## 実行
トップディレクトリ直下の `AlicesMusicFlight` (もしくは `.exe` 拡張子がついたもの) を起動する

## 遊び方
遊びたい曲を選択します
曲が始まったら右からノーツが迫ってくるので, 赤なら上キー, 青なら下キーを押します.
曲が終わったらESCを押して終了してください.
リザルトやスコア機能は未実装です.

## 曲の追加と譜面エディタ
### 曲の追加
1. `charts` ディレクトリ以下に `.chart` で終わるディレクトリを作成します.
2. 遊びたい曲を `song.ogg` としてそのディレクトリに放り込みます.
3. 曲のカバーアートを `bg.png` としてそのディレクトリに放り込みます

### 譜面エディタ
```
% ChartEditor.exe charts/譜面ディレクトリ
```

#### 操作方法
```
                     [U][I]  [P]
        [D][F]     [H][J][K][L]
[Ctrl] [S]           [N] 
[Shift]                   [^]
            [Space]    [<][V][>]
```

- `[Space]` : 曲の再生/一時停止
- `[H][L]` : 曲の停止時に時間を進める/戻す(Vimの左右移動)
- `[F]` : トレースを選択する.
- `[N][P]` : 選択中のトレースの次/前のものを選択する(Next, Prev)
- `[J][K]` : 選択中のトレースの高さを変える
- `[I][U]` : 現在位置にトレースを挿入(Insert, Uはトリルを打ちやすくするため)
- `[D]` : 選択中のトレースとそれにバインドしたノーツを削除する
- `[^][V]` : 選択しているトレースにノーツを挿入する. その後次のトレースを選択する.
- `[<][>]` : 使用しない.

- `[Shift]`を押しているとき
    - `[H][L]` : ゆっくりと時間移動
    - `[J][K]` : 選択したトレースを左右にゆっくりと移動
    - `[^][V]` : 選択したトレースにバインドしたノーツを削除

- `[Ctrl]`を押しているとき
    - `[S]` : 保存

## ライセンス (License)
特に指定がない限り MIT ライセンス.
Resources on this repository is licensed under MIT License UNLESS OTHERWISE SPECIFIED.

<a rel="license" href="http://creativecommons.org/licenses/by-nc/4.0/"><img alt="クリエイティブ・コモンズ・ライセンス" style="border-width:0" src="https://i.creativecommons.org/l/by-nc/4.0/88x31.png" /></a><br /><a xmlns:cc="http://creativecommons.org/ns#" href="https://github.com/ryu-raptor/amf.git" property="cc:attributionName" rel="cc:attributionURL">ryu-raptor</a> 作『<span xmlns:dct="http://purl.org/dc/terms/" href="http://purl.org/dc/dcmitype/Sound" property="dct:title" rel="dct:type">Hitodenashi ReEdit v2</span>』は<a rel="license" href="http://creativecommons.org/licenses/by-nc/4.0/">クリエイティブ・コモンズ 表示 - 非営利 4.0 国際 ライセンス</a>で提供されています。

