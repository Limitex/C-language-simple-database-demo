# C-language-simple-database-demo

## 1. 読み込めるファイルについて
csv形式のファイルで、空白セルがないものが読み込めます。
一行目は列名である必要があります。
読み込める行数に制限はありませんが、一行の文字数とセルの文字数をプログラム内で定数にしているため、それ以下である必要があります。
データは全て文字列として読み込みます。

## 2. 実行できるコマンドについて
コマンドはSQLを模していますが、サブクエリなどは実行できません。
コマンドの詳細は"info help"コマンドで確認できます。
また、入力する文字列に""は使用できないため、データ入力時に１つのデータにスペースを挿入することはできません。
全てコマンドの単語の区切りとして区別されます。
以下に書式と例を示します。
例にあるデータ名などは、実行時に読み込んだデータに沿った名称にする必要になります。
[] <- 必要な文字列
() <- あってもなくても良い文字列
... <- 複数のデータを指定できます

### 0. where
データがどこにあるかを指定して抽出します。
先頭に指定できる句ではないですが、select句とupdate句で共通で使用方法が同じです

比較文字列 <- (>, <, =, >=, <= のどれかを指定できます)

書式
```
where [列名] [比較文字列] [値]
```

例
```
where age <= 50 
where ID = 100
```

### 1. select
データを抽出します。
order_by句を使用することで昇順、降順にソートできます。DESCを付加することで降順になります。

書式
```
select [列名... or *] (where 列名 比較文字列 値) (order_by 列名 (DESC))
```

例
```
select *
select ID name age
select * where ID <= 10
select * where age > 50 order_by age
select name age order_by age DESC
select age name order_by age where name > NameValue
select ID name age where ID <= 200 order_by ID DESC
```

### 2. update
データの値を上書きできます

書式
```
update [列名] = [値] (where 列名 比較文字列 値)
```

例
```
update name = takashi where ID = 10
update age = no_set where ID < 500
update flug = false
```

### 3. insert
データを末尾に追加します。
空白セルを作ることができません。

書式
```
insert [値...]
```

例
```
insert takashi 20 090XXXXXXXX hukuoka
```

### 4. info
データの情報を表示します

指定
column : 列名の一覧を表示します
count  : 行の数を表示します
help   : コマンドの書式を表示します。

書式
```
info [指定]
```

## 3. ビルドについて
vscodeで作成しているため、`.vscode`ディレクトリが存在します。
ターミナル上で`main.c`があるディレクトリに移動し、以下のコマンドを実行してもコンパイルできます。

```
gcc -o main main.c str_read/str_read.c database/database.c commands/extract/extract.c commands/extract/where.c commands/info.c commands/insert.c commands/select.c commands/update.c
```