# リソースファイル

シンプルなペア構造

iniファイルのサブセット
リソースファイル管理用の特殊文法がある.
再帰構造で用いられる前提.

## 構造
```
[Category]
Key : Value
```

## 実装
単純な辞書

```
std::unordered_map<std::string as `Category`, std::unordered_map<std::string as `Key`, std::string as `Value`>>
```

## 拡張機能
1. 変数展開
Valueにて
```
${Category : Key}
```

2. 再帰的読み込み
```
ResourceFiler::_ctor("ResourceInfo.ini", withdir: "ResourceDirectory");
```

withdirにはキー. それぞれのディレクトリに入って再帰的にResourceInfo.iniを読み込む
