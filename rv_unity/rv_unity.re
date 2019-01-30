#@# review-pdfmaker config.yml

= はじめに
== この本について

この本では「Unityでサンプルゲームは作ってみたけどそれからどうしたらいいかわからない」
「入門レベルより少しクオリティの高いゲームを作ってみたい」，というようなUnity初心者～中級者手前の人をターゲットにしています．

なお，この本では画面の見方や操作など基本的な部分の説明は省略することが多いです．
またプログラミングは制御文，関数，クラスなどの基本文法も説明を省かせていただくので分からない場合適宜調べるか一度入門サイトでミニゲームを作ってみることをおすすめします．

== 開発環境
以下の環境・ソフトで開発しました．

: Windows10
 一般的なOS．UnityはMac版でも操作は基本的に同じですが，今回のテーマのアーケード制作においてWiiリモコンやペダルの入力をMacでは方法を載せていませんのでご了承ください．Linuxも同様です．

: Unity2018.3.2f1
 今回のメインで使うゲームエンジン．3Dゲームを作るのに最適で個人からゲーム会社まで広い場所で使われています．

: blender
 フリーの3Dモデリングソフト．造形からテクスチャのマッピング，アニメーション作成までできます．3Dビューの操作が独特で混乱しがち．

: Visual Studio 2017
 Unityでスクリプトを書くときに使います．自動でUnity環境の補完をしてくれます．

= Unityでゲーム部分を作ろう
== プロジェクトを作成する
Unityを起動し「New」から新規に作るプロジェクトの設定をします．
Project nameは「shoot」など任意の名前，Templateは「3D」，他パスの設定などしてCreate projectでプロジェクトを作成します．

== 地形を作る
ゲームの舞台となる地形を作ります．Unityには山や植物をペイントツールのように作るTerrainという機能があります．

=== Standard Assetsのインポート
Terrainを使う前に，地面に適用するテクスチャや草木のデータを使うために公式の「Standard Assets」をインポートします．

UnityのAsset Storeから「Standard Assets」で検索するとパッケージが出てくるのでダウンロードし，インポートします．
インポート時に色々選択できますが，必要なテクスチャや草木データが入っている「Environment」のみでいいでしょう．

//image[1_1][Standard Assets][scale=0.5]{
//}

=== Terrainの設置
「Hierarchy」の「Create」から「3D Object>Terrain」で作ります．
「Inspector」の「Terrain」で設定ができ，「Paint Texture」を選択し「Edit Terrain Layers」から草のテクスチャ画像を指定しましょう．
//image[1_2][草テクスチャの指定][scale=0.7]{
//}

== 敵(ゾンビ)の用意
恐らく一番難しい敵キャラの動作を作ります．

ゾンビが今回唯一登場するキャラクターです．アニメーションやラグドール，移動AIなど初心者には難しいところがあるかもしれませんが，
ここを作ることができると”ゲーム感”がとてもよく出てそれっぽくなります．

=== ゾンビのモデルをインポート
Asset Storeで「zombie」と検索すると出てくる一番人気のアセットをインポートします．
//image[1_3][ゾンビの素材][scale=0.8]{
//}
筆者はこの時なぜかインポートしたファイル名の一つが大文字小文字の区別に関するエラーが出てきたので手動で修正しました．

=== ゾンビの死体を作る
恐ろしい小見出し名ですが，ゾンビを撃った後に物理法則に従って倒れるようにラグドールを適用します．
インポートしたアセットのPrefabsというフォルダにゾンビのプレハブがあるのでシーンに追加し，メニューの
「GameObject>3D Object>Ragdoll...」からCreate Ragdollウィンドウを開きます．

頭，腕，足など指定するためシーンのゾンビの階層を展開してドラッグアンドドロップで一つずつ体のパーツを当てはめていきます．
//image[1_5][ラグドールの設定][scale=1]{
//}

enemyタグ付ける


== ゾンビを撃つスクリプトを書く
ここでゲームの動作部分になるプログラムを作ります．「ShotCam」という名前でスクリプトを新規作成し@<fn>{script}，以下のコードを書きます．

スクリプトはMain Cameraにアタッチします．
//footnote[script][UnityではC#の他JavaScript,Booといったプログラミング言語を使えましたが，廃止となっています．]
//emlist[ShotCam.cs][c#]{
public class ShotCam : MonoBehaviour {
  void Start() {
  }
  void Update() {
    GameObject clickObject=getClickObject();
    //クリックしたのが敵なら
    if (clickObject!=null && clickObject.gameObject.tag == "enemy") {
      //アニメーション無効
      clickObject.transform.root.GetComponent<Animator>().enabled = false;  
      Vector3 vec = clickObject.transform.position - this.transform.position;
      //射撃した部位に力を加える
      clickObject.GetComponent<Rigidbody>().velocity = vec.normalized*15;
      //ゾンビ側のスクリプトのdeath()呼び出し
      clickObject.transform.root.GetComponent<Zombie>().death();  
    }
  }
  // 左クリックしたオブジェクトを取得する関数
  public GameObject getClickObject() {
    GameObject clickObject = null;
    if (Input.GetMouseButtonDown(0)) {  //左クリック
      Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
      RaycastHit hit = new RaycastHit();
      if (Physics.SphereCast(ray, 0.1f, out hit)) {
        clickObject = hit.collider.gameObject;
      }
    }
    return clickObject;
  }
}
//}

続いてゾンビのオブジェクト(一番上の階層)にZombieというスクリプトを作成し以下のクラスを追加しアタッチします．

//emlist[Zombie.cs][c#]{
  public void death() {
    Invoke("destroyObject", 5f);　//5秒後に実行
  }
  void destroyObject() {
    Destroy(gameObject);  //オブジェクトを消す
  }
//}

=== プログラム解説
まずはShotCamの説明をします．

getClickObject関数は左クリックされると画面上にRayと呼ばれるレーザーのような線を出し，衝突したオブジェクトを取得しreturnで返しています．
毎フレーム呼び出されるUpdate関数ではgetClickObject関数でクリックしたオブジェクトを検知し続け，if文にてenemyタグが付いているかを判別します．
enemyタグはゾンビの胴体，手足，頭についておりclickObject.transform.rootでいずれからも一番上の階層のオブジェクト「Zombie」のアニメーションを参照でき，無効にしています．

変数vecは撃った部位に力を加えて吹き飛ぶ演出をするためのベクトルを保持しています．撃った部位の座標からゲーム画面を映すカメラの座標を減算することでベクトルが取得できます．
そしてnormalizedで単位ベクトル化しRigidbodyコンポーネントで力を加えています．「*15」は力の大きさです．試しに大きくして遊んだり自分好みの値にしてみるのもいいでしょう．

ベクトルが分からない，という人もいるかと思いますが下の図の「矢印」がベクトルだと思ってください．ベクトルは方向と力の情報を持っていて座標点b-座標点aでaからbへのベクトルになります．
その「矢印」をゾンビ撃った部位に付けることでその点に力が加わる，ということになります．

最後にゾンビ側のスクリプトZombie.csの関数deathを呼び出して一定時間後オブジェクトを消すようにしています．

Zombie.csではn秒後に何かをする，という動作のためInvoke関数を使っています．これは第一引数に関数名，第二引数に秒数を指定することで指定秒数後に関数を呼び出す便利な機能です．
そして呼び出す関数ではDestroyでゾンビ本体を丸ごと削除しています．


===[column] Unityで使われるクラス
Vector3は3D空間のベクトルを扱うための関数です．x,y,zの要素を持っています．