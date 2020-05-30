# Syncの計算
sync rhythm tempo startms

speed := 1小節あたりの時間(s)
musiccounter := 音楽の現在再生時刻(s)
stagecounter := ゲームの再生位置(s)
sectionno := 小節番号
sectionpos := 小節を1とした時の位置
|==== ==== ==== ====|
0         0.5       1

tempo = [rythm / minutes]
sectiontempo[Section / minutes] = tempo * [rhythmの分子]
speed = 1 / (sectiontempo * 60)

stagecounter = musiccounter - startms
sectionno = floor(stagecounter / speed)
sectionpos = (stagecounter - (sectionno * speed)) / speed
           = (stagecounter / speed - sectionno)

## stage counterの進め方
fore = getTimeTick()
loop {
do some work
now = getTimeTick()
sec = toSeconds(now - fore)
stagecounter += sec
fore = getTimeTick()
}

# 音ズレ
どんなに高性能なパソコンでも音ズレは起きる.
それの訂正が大事.

      V    0
game: ==== | ==== ==== ==== ==== |
muse: --- | ---- ---- ---- ---- |

0 の地点になったらstagecounter <- musiccounterにする.

          V
game: === | ==== ==== ==== ==== |
muse: --- | ---- ---- ---- ---- |

nextscoutner = (sectionno + 1) * speed
loop {
if stagecounter >= nextscoutner {
stagecounter = musiccounter
nextscoutner = (sectionno + 1) * speed
}
