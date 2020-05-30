# 各ファイルのフォーマット

songname.chart
|- trace
|- note
|- info

## trace
~~~
[trace timming(s)] [trace height]
...
~~~

- **trace timming** : トレースの時刻(s)
- **trace height** : トレースの高さ

## note
~~~
[ButtonIdentifier] [notes type] ([trace]...)
...
~~~

- **ButtonIdentifier** : 0 = 上, 1 = 下
- **notes type** : 0 = tap, 1 = press
- ([trace]...) : そのノーツ特有の引数. 一般にそのノーツを配置するトレースの番号. (トレースファイルの上から順に0, 1, ...)

### notes type
- tap <- (Trace)

タッチのみ受け付ける
引数のトレースはそのノーツの位置

- press <- (Trace1, ..., TraceN)

長押しノーツ
引数はそのノーツがたどるトレース
間すっぽかすと変なことになるのでやらないように
