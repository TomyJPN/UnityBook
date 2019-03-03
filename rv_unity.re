#@# review-pdfmaker config.yml

= はじめに
== この本について
「Unityを使えば簡単にゲームを作れる！」と聞いてダウンロードし，入門サイトを見ながら簡単なゲームはどうにかできたけど，
その後どうすればいいの・・・と悩んでしまった方も多いのではないでしょうか．
この本では「入門レベルよりちょこっとクオリティの高いゲームを作ってみたい」「弾転がしとかブロック崩しはもういい」「もっとUnityのいろんな機能を使いたい」
というようなUnity初心者～中級者手前の人をターゲットにしています．

また，タイトル通り文化祭などで"映える"アーケードゲームを作ることをメインとしています．
アーケードと言っても，Wiiリモコンと自作ペダルのみの単純なものですが，シンプルかつ直感的な操作性は子どもや非ゲーマーでも楽しめると思います．

なお，この本ではUnity画面の見方や操作など基本的な部分や，機能の説明は省略することが多いです．
プログラミングのC#における基本文法も説明を省かせていただくので，疑問が浮かんだときや詰まった時は適宜調べるか，一旦入門サイトや書籍でミニゲームを作ってみることをおすすめします．

== 開発環境
: Windows10
 一般的なOS．UnityはMac版でも操作は基本的に同じですが，今回使うWiiリモコンやペダルのMacでの入力方法は対象外とさせて頂きますのでご了承ください．

: Unity2018.3.2f1
 今回のメインで使うゲームエンジン．3Dゲームを作るのに最適で個人からゲーム会社まで広い場所で使われています．以前はUnity4，Unity5のような言い方でしたが，201xというバージョンナンバリングに変わりました．

: blender
 フリーの3Dモデリングソフト．造形からテクスチャのマッピング，アニメーション作成までできます．3Dビューの操作が独特で混乱しがち．

: Visual Studio 2017
 Unityでスクリプトを書くときに使います．Unity環境の補完もしてくれます．

= Unityでゲーム部分を作ろう
ゾンビを射撃するFPSゲームを今回作ります．
Wiiリモコンで撃てるようにしたいのですが，Unityで作るときはWindowsのマウスのクリックで入力できればOKです．

この章では制作の順を追って解説していきます．

== プロジェクトを作成する
Unityを起動し「New」から新規に作るプロジェクトの設定をします．
Project nameは「shoot」など任意の名前，Templateは「3D」，他パスの設定などしてCreate projectでプロジェクトを作成します．

== 地面を作る
ゲームの舞台となる地形を作ります．Unityには山や植物をペイントツールのように作る「Terrain」という機能があります．

=== Standard Assetsのインポート
「Terrain」を使う前に，地面に適用するテクスチャや草木のデータを使うために公式の「Standard Assets」をインポートします．

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
今回メインの作業である敵キャラの動作を作ります．

ゾンビが今回唯一登場するキャラクターです．人型の3Dモデルを扱う際，アニメーションやラグドール，移動AIなど初心者には難しいところがあるかもしれませんが，
ここを作ることができると”ゲーム感”がとても出て感動も大きいはずです．

=== ゾンビのモデルをインポート
Asset Storeで「zombie」と検索すると出てくる一番人気のアセットをインポートします．
//image[1_3][ゾンビの素材][scale=0.8]{
//}
筆者はこの時インポートしたファイル名の一つが，大文字小文字の区別に関するエラーがなぜか出てきたので手動で修正しました．

=== ゾンビの死体を作る
恐ろしい見出し名ですが，ゾンビを撃った後に物理法則に従って倒れるようにラグドールを適用します．
ラグドールとは，洋ゲーとかで敵が死ぬとぐったり人形のように崩れていくアレです．
インポートしたアセットの「Prefabs」というフォルダにゾンビのプレハブがあるのでシーンに追加し，メニューの
「GameObject>3D Object>Ragdoll...」からCreate Ragdollウィンドウを開きます．

頭，腕，足など指定するためシーンのゾンビの階層を展開して，ドラッグアンドドロップで一つずつ体のパーツを当てはめていきます．
//image[1_5][ラグドールの設定][scale=1]{
//}

=== タグを付ける
この後ゾンビを撃つスクリプトを書きますが，プログラムで識別するためのタグをつけます．
インスペクタの「Tag＞add tag」から「enemy」と名付けたタグを追加し，ゾンビのコライダがついているオブジェクト全てに適用しましょう．
階層をshiftキーで推しながら複数選択してからTagを設定すると，一度に付けることができます．
//image[1_5_2][tagの設定][scale=1]{
//}



== ゾンビを撃つスクリプトを書く
ここでゲームの動作部分になるプログラムを作ります．「ShotCam」という名前でスクリプトを新規作成し，@<fn>{script}以下のコードを書きます．

スクリプトはMain Cameraにアタッチします．
//footnote[script][UnityではC#の他JavaScript,Booといったプログラミング言語を使えましたが,廃止となっています．]
//emlist[ShotCam.cs][c#]{
public class ShotCam : MonoBehaviour {
  void Start() {
  }
  void Update() {
    GameObject clickObject = getClickObject();
    if (clickObject == null || clickObject.gameObject.tag != "enemy") {
      return;
    }

    //クリックしたのが敵なら
    Vector3 vec = clickObject.transform.position - this.transform.position;
    //射撃した部位に力を加える
    clickObject.GetComponent<Rigidbody>().velocity = vec.normalized * 30;
    //ゾンビ側のスクリプトのdeath()呼び出し
    clickObject.transform.root.GetComponent<Zombie>().death();
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

続いてゾンビのオブジェクト(一番上の階層)にZombieというスクリプトを作成し，以下のクラスを追加しアタッチします．

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

getClickObject関数は，左クリックされると画面上にRayと呼ばれるレーザーのような線を出し，衝突したオブジェクトを取得しreturnで返しています．
毎フレーム呼び出されるUpdate関数では，getClickObject関数でクリックしたオブジェクトを検知し続け，if文にてenemyタグが付いているかを判別します．

変数vecは撃った部位に力を加えて吹き飛ぶ演出をするためのベクトルを保持しています．撃った部位の座標からゲーム画面を映すカメラの座標を減算することで，ベクトルが取得できます．
そしてnormalizedで単位ベクトル化し，Rigidbodyコンポーネントで力を加えています．「*15」は力の大きさです．試しに大きくして遊んだり自分好みの値にしてみるのもいいでしょう．

#@#ベクトルが分からない，という人もいるかと思いますが下の図の「矢印」がベクトルだと思ってください．ベクトルは方向と力の情報を持っていて，座標点b-座標点aでaからbへのベクトルになります．
#@#その「矢印」をゾンビ撃った部位に付けることでその点に力が加わる，ということになります．
enemyタグはゾンビの胴体，手足，頭につけているので，clickObject.transform.rootでいずれからも一番上の階層のオブジェクトから，Zombie.csの関数deathを呼び出せます．

関数deathが呼び出されるとアニメーションを無効にして5秒後に消す処理を行います．アニメーションが無効になると魂が抜けたようにふっと体が崩れ(=ラグドールにより倒れ)ます．

シーンのカメラに見える位置にゾンビを設置し，Unityの三角ボタンで実行してみましょう．
クリックするとゾンビが吹き飛ぶとOKです．
//image[1_6_3][実行結果(クリックすると倒れる)][scale=1]{
//}


== ゾンビを歩かせる
ゾンビをプレイヤーまで歩かせるために，経路に沿って移動していくAgentとアニメーションとして体が動くAnimatorの二つの機能を使います．
=== 経路探索AIの実装
Unityには嬉しいことに経路探索AIが自動で入っています．まず，ゾンビに「Nav Mesh Agent」のコンポーネントを追加し図のように設定します．
//image[1_8][Nav Mesh Agentの設定][scale=0.7]{
//}
次に「Terrain」に経路探索のために必要な作業をします．「Terrain」を選択するとインスペクタの隣に「Navigation」というタブが出てきます．
選択し「Bake」からパラメータを調整してBakeすることで，ゾンビが歩ける場所が青く表示されます．

なお，試しに障害物として画像ではCubeを置いていますが，インスペクタから「static」にチェックを入れるのを忘れないようにしてください．
//image[1_9][経路となる領域をBakeした様子][scale=0.9]{
//}

=== アニメーション遷移の実装
移動中には歩くアニメーション，止まるときには待機のアニメーションを適用するためAnimatorの設定をします．
アセットにwalk，idle，atackのアニメーションが含まれているのでノードと遷移を設定します．
矢印はノードを右クリックし，「Make Transition」を選択します．
矢印を選択したときにインスペクタに表示されるConditionsで「state」と名付けたint型の遷移条件変数を追加し，walkへの矢印にはEquals 0，idleへはEquals 1を割り当てます．
遷移条件変数はAnimatorウィンドウ左のParametersで「＋」マークを押すと作成できます．

また，矢印を選択したときにインスペクタに表示される@<b>{「Has Exit Time」のチェックは外してください}．これはstateの変更があった時にアニメーションを中断してすぐに切り替えるためです．
チェックが付いたままですと，例えばゾンビが立ち止まったのに，アニメーションでは一瞬歩く動作のままで滑るような動きをしてしまいます．

攻撃アニメーションのノード「attack」に関しては，後で実装するので今は矢印を付けなくていいです．

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
    private enum state { walk, idle }  //アニメーションの状態
    private Animator animator;
    void Start() {
      camera = GameObject.Find("Main Camera").gameObject;
      agent = GetComponent<NavMeshAgent>();
      agent.SetDestination(camera.transform.position);  //目標座標を設定
      stop = false;
      animator = GetComponent<Animator>();
      SetKinematic(true);  //物理演算を無効にする
    }
    void Update() {
      //ゾンビが目標点まで2m近づいたら立ち止まる
      if (stop ||
          Vector3.Distance(camera.transform.position, this.transform.position) >= 2f) 
      {
        return;
      }

      animator.SetInteger("state", (int)state.idle);
      Vector3 p = camera.transform.position;
      p.y = this.transform.position.y;
      transform.LookAt(p);
      agent.isStopped = stop = true;
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

=== プログラム解説
Start関数では，ゾンビが目的地とするカメラの取得と座標設定，Animatorの取得をしています．

Update関数では，ゾンビがカメラまで近づいたら動作する処理があり，stateを待機(idle)にアニメーションを切り替え
カメラの方向を向き，移動を停止しています．

そしてdeath関数の変更とSetKinematicという関数の追加も行っています．これは，NavMesh AgentとAnimator，ラグドールを併用したために必要となったプログラムです．
公式ドキュメントでは，NavMesh AgentはPhysicsと合わせて使用するのを非推奨としています．キャラの動きをNavMesh Agentで行っているのにそれに物理トリガを加えたりアニメーション動作を加えると競合してしまうからです．
そこで，NavMesh Agentで動かしている，すなわちゾンビが生きている(?)状態ではRigidbodyのIs Kinematicをオンにして物理演算を無効にし，撃たれて死ぬ状態ではNavMesh AgentをオフにしつつIs Kinematicをオンにすることでラグドールを動作させるやり方にしています．
SetKinematic関数はそのために子オブジェクトが持つRigidbodyコンポーネント全ての物理演算を切り替えるものです．

これでプレビューを実行してみると，ゾンビがカメラに向かって歩きだし，近づくと立ち止まります．

== ゾンビにプレイヤーを攻撃させる
さて，現状ではゾンビがただプレイヤーにわらわら集まってくるだけです．ゾンビのモッシュですね．
ですがゾンビはライブのパリピではなく人間を喰らう存在ですので，攻撃するよう実装していきましょう．

=== animatorで攻撃の遷移を設定する
attackに画像のように矢印を付けますが，attackへの遷移条件は「attack」Trrigerが呼び出されたときという設定になります．
そしてattackからidle，waklへの遷移は「Has Exit Time」のチェックを付けるのみにします．

//image[1_14][animatorの設定][scale=0.9]{
//}
//image[1_13][attackへの遷移条件][scale=0.9]{
//}

=== カメラの揺れ演出の準備
ゾンビが攻撃するようになったのでプレイヤーがダメージを負う演出を加えます．
ゾンビが攻撃するとカメラを揺らすのですが，一からコードを書くと面倒なのでiTweenというAssetを使おうと思います．
これまでと同じように「iTween」とAsset Storeで検索，インポートしたら準備は完了です．

=== プログラムを書き換える
攻撃動作を付けるためにZombie.csを書き換えます．攻撃は指定秒ごとに行うようにするため，以下のように時間を管理するメンバ変数を定義します．
//emlist[Zombie.cs][c#]{
  private float timeOut;
  private float timeElapsed;
//}
そしてStart関数内にtimeOutの初期化を追加．
//emlist[Zombie.cs][c#]{
  timeOut = 3f;
//}
Update関数に以下のコードを追加します
//emlist[Zombie.cs][c#]{
  timeElapsed += Time.deltaTime;
  if (timeElapsed < timeOut || !stop) {
    return;
  }
  
  animator.SetTrigger("attack");
  timeElapsed = 0.0f;
  Invoke("damage", 0.9f);
//}
最後に，以下の関数を追加します．
//emlist[Zombie.cs][c#]{
  void damage() {
    //ゾンビが死んでいたら無効
    if (!agent.enabled) {
      return;
    }

    iTween.ShakePosition(camera, iTween.Hash("x", 0.1f, "y", 0.1f, "time", 1f));
  }
//}

=== プログラム解説
Time.deltaTimeには，最後のフレームからの経過時間[ms]が格納されています．
Update()が実行されるたびに経過時間を積み上げていき，指定した時間を超えたら望みの処理を実行するようにします．

ゾンビが攻撃をしたらアニメーションが開始されますが，開始から0.9秒後と指定してカメラをiTweenで揺らしています．
0.9秒は攻撃アニメーションが開始されてから引っ搔かれてダメージを負うのに丁度いい時間となっています．

しかし，この仕様のままだと”攻撃アニメーションが開始”された後から0.9秒以内にゾンビを撃った場合，ゾンビが倒れたのにダメージ演出が呼び出されてしまいます．
そこで，NavMesh Agentが有効かどうかでif判定を行っています．フラグ変数を作ってもいいのですが，簡略化のためこのようにしました．

===[column] 便利なiTween
めっちゃ便利～～～～～～！
position,rotate色々

== エフェクトを付ける
ゲームの見栄えを良くするためにエフェクトを使うことは効果的です．
プレイヤーに”撃った感”を感じてもらうため, 着弾点に爆発のようなエフェクトを付けます．
エフェクトはUnityのパーティクルシステムという機能で作成することも可能ですが，今回はAsset Storeで無料の素材をお借りしましょう．

Asset Storeで「War Fx」と検索すると爆発や炎，銃撃などが入ったアセットが見つかります．
//image[1_11][War Fx][scale=0.9]{
//}

インポートしたら次に，ShotCam.csを改造します．
クラスのメンバ変数として

//emlist[ShotCam.cs][c#]{
  public GameObject hitEffect;
//}
 
と宣言し，getClickObject関数内のif文に以下のように一行追加します

//emlist[ShotCam.cs][c#]{
  if (Physics.SphereCast(ray, 0.1f, out hit)) {
    clickObject = hit.collider.gameObject;
    //[追加]着弾点エフェクト
    Instantiate(hitEffect, hit.point, Quaternion.identity);
  }
//}

そしてhitEffectはpublicで宣言しているため，Main Cameraのインスペクタから手動でアタッチする必要があります．
先ほどインポートしたアセットの「JMO Assets>WarFX>_Effects>Explosions>WFX_Explosion Small」をドラッグ&ドロップでアタッチします．
実行してみるとわかりますが，エフェクトが大きすぎて不自然です．そこでエフェクトのScaleをx，y，z全部0.3にしたら丁度よくなりました．
エフェクトを変えてもプログラム自体は変える必要ないので他のアセットやサイズ，オリジナルエフェクトなど試してみるのもいいでしょう．
//image[1_12][War Fx][scale=0.9]{
//}

=== 動作確認
さて，ラグドール，アニメーション，Navmesh Agent，エフェクトなど様々な実装をしましたがいかがだったでしょうか．
Null参照などのエラーが出る場合，コンソールをダブルクリックすることで原因となる処理のソースが分かることもあります．

正しく実行できている場合，図のようにゾンビが経路に従い歩き，カメラに近づくと攻撃，カメラが揺れます．
ゾンビを撃つと火花のエフェクトとともにゾンビが吹き飛びます．

//image[1_15][実行結果][scale=1]{
//}

= マップのモデリング
さて，一章ではゲームの基本システムを作成しました．しかし地平線やただの地形だけの背景だとどうしても寂しいですよね．

そこでゲームには不可欠なマップの作成ですが，今回はモデリングによるオリジナルマップ作成を簡単にご紹介しようと思います．
この本で扱うゲームはどんなマップでも基本遊べますので，この章はスキップしてアセットストアの無料マップを使っても大丈夫です．

== blenderによるモデリング
今回は無料の3Dモデリングソフト「blender」を扱います．少々(少々か？)操作に癖のあるソフトですがモデリング，テクスチャマッピング，ボーンやアニメーションの作成など一通りの機能を揃えています．
日本語にも対応しており，設定で切り替えられます．

=== 実際にある建物のモデリング
開発者の趣味でゲームを作っているとき，マップはどうすればいいでしょうか．ゾンビを倒すゲームということで王道の荒廃した架空の都市などもいいでしょう．
しかし今回は少し捻って実際に存在する場所を舞台にしてみます．今回は最近流行りの某アニメをパロって佐賀駅をモデリングしちゃいます．ゾンビに溢れ荒れる佐賀駅，いいですね．
インターネットミームで海底都市SAGAとかありますが，筆者のゲームでは屍都市SAGAです．何にでもなれるのが佐賀の魅力だと思います(？)．

なお，この章では佐賀駅を例としていますが，最寄り駅，学校，勤務先など任意の荒らしたい舞台にしちゃっていいです．むしろそうしましょう．

=== 素材となる資料
実在する建物の場合おすすめはGoogleMAPの航空写真です．細かい部分はストリートビューで見ることもでき，3Dビュー対応の地域だと色々な角度から見えます．

//image[2_1][佐賀駅の3Dビュー][scale=0.8]{
//}

航空写真はblenderの「下絵」機能を使って寸法を再現するのに使います．高さは感覚での調整になりますが，これだけで再現度が上がりリアルになります．

シンプルな建築物の3Dモデリングの基本は，立方体の「分割」と「押し出し」の繰り返しです．

blenderは沢山の操作ができショートカットキーも同じように覚えきれないほどあります．
しかし基本的に立方体の押し出しの組み合わせで作る程度ですと，最低限の操作さえ把握していれば作ることができます．

以下，筆者が良く使うショートカットキー一覧です．逆にこれ以外は使わなくてもほぼ作ることができると思います．
//table[camp][ショットカットキー]{
ショートカット	操作	説明
----------------------------
Tab	モード切替	オブジェクトモードと編集モードに切り替える
G	移動	選択している部分の座標を変更する
R	回転	選択しているオブジェクトを回転させる
S	拡大縮小	選択している部分を拡大縮小する
E	押し出し	選択した頂点・辺・面を押し出す
W	細分化	ポリゴンを分割する
Ctrl+R	ループカット	選択した辺に隣接している全ての面を繋げてカットする
Ctrl+B	面取り	角を丸める
X/Y/Z	軸選択	上記の編集中に押すことで各軸ごとに移動や押し出しができる
//}

//image[2_2][下絵機能を使い上から見た形を作る様子][scale=0.7]{
//}
#@#//image[2_4][佐賀駅の3Dビュー][scale=0.8]{
#@#//}
//image[2_3][横側に「押し出し」ている様子][scale=0.7]{
//}
//image[2_5][モデリングした佐賀駅南口][scale=0.7]{
//}

== テクスチャのマッピング
モデリングをしたら建物の形はできますが単色でのっぺりしたままです．そこでモデルの平面に画像を張り付けて質感を与えます,これをテクスチャマッピングといいます．
blenderでは

===[column] タイトル
ここにコラムをかける

改ペ～～～ジ！
//embed[latex]{
\clearpage
//}