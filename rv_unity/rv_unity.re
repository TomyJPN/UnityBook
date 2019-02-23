#@# review-pdfmaker config.yml

= はじめに
== この本について

この本では「Unityでサンプルゲームは作ってみたけどそれからどうしたらいいかわからない」
「入門レベルより少しクオリティの高いゲームを作ってみたい」，というようなUnity初心者～中級者手前の人をターゲットにしています．

また，文化祭などで"映える"アーケードゲームを作ることをメインとしています．Wiiリモコンを使ったシンプルな操作性は
子どもでも遊びやすくウケがいいです(体験談)．

なお，この本ではUnity画面の見方や操作など基本的な部分の説明は省略することが多いです．
プログラミングはC#における基本文法も説明を省かせていただくので分からない場合適宜調べるか一度入門サイトでミニゲームを作ってみることをおすすめします．

== 開発環境
以下の環境・ソフトで開発しました．

: Windows10
 一般的なOS．UnityはMac版でも操作は基本的に同じですが，今回使うWiiリモコンやペダルのMacでの入力方法は対象外とさせてもらうのでご了承ください．Linuxも同様です．

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
筆者はこの時インポートしたファイル名の一つが大文字小文字の区別に関するエラーがなぜか出てきたので手動で修正しました．

=== ゾンビの死体を作る
恐ろしい見出し名ですが，ゾンビを撃った後に物理法則に従って倒れるようにラグドールを適用します．
ラグドールとは，洋ゲーとかで敵が死ぬとぐったり人形のように崩れていくアレです．
インポートしたアセットのPrefabsというフォルダにゾンビのプレハブがあるのでシーンに追加し，メニューの
「GameObject>3D Object>Ragdoll...」からCreate Ragdollウィンドウを開きます．

頭，腕，足など指定するためシーンのゾンビの階層を展開してドラッグアンドドロップで一つずつ体のパーツを当てはめていきます．
//image[1_5][ラグドールの設定][scale=1]{
//}

=== タグを付ける
この後ゾンビの撃つスクリプトを書きますが，プログラムで識別するためのタグをつけます．
インスペクタの「Tag＞add tag」から「enemy」と名付けたタグを追加し，ゾンビのコライダがついているオブジェクト全てに適用しましょう．
階層をshiftキーで推しながら複数選択してからTagを設定すると一度に付けることができます．
//image[1_5_2][tagの設定][scale=1]{
//}



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
      Vector3 vec = clickObject.transform.position - this.transform.position;
      //射撃した部位に力を加える
      clickObject.GetComponent<Rigidbody>().velocity = vec.normalized*30;
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
      Debug.Log(clickObject);
    }
    return clickObject;
  }
}
//}

続いてゾンビのオブジェクト(一番上の階層)にZombieというスクリプトを作成し以下のクラスを追加しアタッチします．

//emlist[Zombie.cs][c#]{
  public void death() {
    GetComponent<Animator>().enabled = false; //アニメーション無効
    Invoke("destroyObject", 5f);　//5秒後に消滅させる
  }
  void destroyObject() {
    Destroy(gameObject);  //オブジェクトを消す
  }
//}

=== プログラム解説
まずはShotCamの説明をします．

getClickObject関数は左クリックされると画面上にRayと呼ばれるレーザーのような線を出し，衝突したオブジェクトを取得しreturnで返しています．
毎フレーム呼び出されるUpdate関数ではgetClickObject関数でクリックしたオブジェクトを検知し続け，if文にてenemyタグが付いているかを判別します．

変数vecは撃った部位に力を加えて吹き飛ぶ演出をするためのベクトルを保持しています．撃った部位の座標からゲーム画面を映すカメラの座標を減算することでベクトルが取得できます．
そしてnormalizedで単位ベクトル化しRigidbodyコンポーネントで力を加えています．「*15」は力の大きさです．試しに大きくして遊んだり自分好みの値にしてみるのもいいでしょう．

#@#ベクトルが分からない，という人もいるかと思いますが下の図の「矢印」がベクトルだと思ってください．ベクトルは方向と力の情報を持っていて座標点b-座標点aでaからbへのベクトルになります．
#@#その「矢印」をゾンビ撃った部位に付けることでその点に力が加わる，ということになります．
enemyタグはゾンビの胴体，手足，頭につけているのでclickObject.transform.rootでいずれからも一番上の階層のオブジェクトからZombie.csの関数deathを呼び出せます．

関数deathが呼び出されるとアニメーションを無効にして5秒後に消す処理を行います．アニメーションが無効になると魂が抜けたようにふっと体が崩れ(=ラグドールにより倒れ)ます．

シーンのカメラに見える位置にゾンビを設置し，Unityの三角ボタンで実行してみましょう．
クリックするとゾンビが吹き飛ぶとOKです．
//image[1_6_3][実行結果(クリックすると倒れる)][scale=1]{
//}


== ゾンビが歩くようにする
ゾンビをプレイヤーまで歩かせるために，経路に沿って移動していくAgentとアニメーションとして体が動くAnimationの二つの機能を使います．
=== 経路探索AIの実装
Unityには嬉しいことに経路探索AIが自動で入っています．まず，ゾンビに「Nav Mesh Agent」のコンポーネントを追加し図のように設定します．
//image[1_8][Nav Mesh Agentの設定][scale=0.7]{
//}
次にTerrainに経路探索のために必要な作業をします．Terrainを選択するとインスペクタの隣に「Navigation」というタブが出てきます．
選択し「Bake」からパラメータを調整してBakeすることでゾンビが歩ける場所が青く表示されます．

なお，試しに障害物として画像ではCubeを置いていますがインスペクタから「static」にチェックを入れるのを忘れないようにしてください．
//image[1_9][経路となる領域をBakeした様子][scale=0.9]{
//}

=== アニメーション遷移の実装
移動中には歩くアニメーション，止まるときには待機のアニメーションを適用するためAnimationの設定をします．
アセットにwalk,idle,atackのアニメーションが含まれているのでノードと遷移を設定します．
矢印はノードを右クリックし，「Make Transition」を選択します．
矢印を選択したときにインスペクタに表示されるConditionsで「state」と名付けた遷移条件変数を追加しwalkへの矢印にはEquals0,idleへはEquals1,attackへはEquals2を割り当てます．

//image[1_10][Animatorの設定][scale=1]{
//}

=== スクリプトを書き換える
経路探索のためにAI機能をインポートします
//emlist[Zombie.cs][c#]{
  using UnityEngine.AI;
//}
そして以下のように書き換えていきます
//emlist[Zombie.cs][c#]{
  public class Zombie : MonoBehaviour {
  private new GameObject camera;
  private NavMeshAgent agent;
  private bool stop;
  private enum state { walk,idle,atack }  //アニメーションの状態
  private Animator animator;
  void Start() {
    camera = GameObject.Find("Main Camera").gameObject;
    agent = GetComponent<NavMeshAgent>();
    agent.SetDestination(camera.transform.position);  //目標座標を設定
    stop = false;
    animator = GetComponent<Animator>();
  }
  void Update() {
    //ゾンビが目標点まで2m近づいたら立ち止まる
    if (!stop && 
        Vector3.Distance(camera.transform.position, this.transform.position) < 2f) 
    {
      animator.SetInteger("state", (int)state.idle);
      Vector3 p = camera.transform.position;
      p.y = this.transform.position.y;
      transform.LookAt(p);
      agent.isStopped = stop = true;
    }
    else {
      //animator.SetInteger("state", (int)state.walk);
    }
  }
  //死ぬ処理
  public void death() {
    GetComponent<Animator>().enabled = false; //アニメーション無効
    Invoke("destroyObject", 5f);　//5秒後に消滅させる
    SetKinematic(false);  //物理演算を付ける
    agent.enabled = false;
  }
  void destroyObject() {
    Destroy(gameObject);  //オブジェクトを消す
  }

  public void SetKinematic(bool newValue) {
    Component[] components = GetComponentsInChildren(typeof(Rigidbody));
    foreach (Component c in components) {
      (c as Rigidbody).isKinematic = newValue;
    }
  }
}
//}


これでプレビューを実行してみると，ゾンビがカメラに向かって歩きだし，近づくと立ち止まります．
また，撃つと

//embed[latex]{
\clearpage
//}

===[column] タイトル
ここにコラムをかける