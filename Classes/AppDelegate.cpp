#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;
using namespace cn::sharesdk;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    //初始化ShareSDK
    C2DXShareSDK::open("api20", false);

    //初始化社交平台信息
    this->initPlatformConfig();

    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void AppDelegate::initPlatformConfig()
{
    //新浪微博
    Dictionary *sinaConfigDict = Dictionary::create();
    sinaConfigDict -> setObject(String::create("568898243"), "app_key");
    sinaConfigDict -> setObject(String::create("38a4f8204cc784f81f9f0daaf31e02e3"), "app_secret");
    sinaConfigDict -> setObject(String::create("http://www.sharesdk.cn"), "redirect_uri");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeSinaWeibo, sinaConfigDict);

    //腾讯微博
    Dictionary *tcConfigDict = Dictionary::create();
    tcConfigDict -> setObject(String::create("801307650"), "app_key");
    tcConfigDict -> setObject(String::create("ae36f4ee3946e1cbb98d6965b0b2ff5c"), "app_secret");
    tcConfigDict -> setObject(String::create("http://www.sharesdk.cn"), "redirect_uri");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeTencentWeibo, tcConfigDict);

    //短信
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeSMS, NULL);

    //QQ空间
    Dictionary *qzConfigDict = Dictionary::create();
    qzConfigDict -> setObject(String::create("100371282"), "app_id");
    qzConfigDict -> setObject(String::create("aed9b0303e3ed1e27bae87c33761161d"), "app_key");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeQZone, qzConfigDict);

    //微信
    Dictionary *wcConfigDict = Dictionary::create();
    wcConfigDict -> setObject(String::create("wx4868b35061f87885"), "app_id");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeWeixiSession, wcConfigDict);
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeWeixiTimeline, wcConfigDict);
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeWeixiFav, wcConfigDict);

    //QQ
    Dictionary *qqConfigDict = Dictionary::create();
    qqConfigDict -> setObject(String::create("100371282"), "app_id");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeQQ, qqConfigDict);

    //Facebook
    Dictionary *fbConfigDict = Dictionary::create();
    fbConfigDict -> setObject(String::create("107704292745179"), "api_key");
    fbConfigDict -> setObject(String::create("38053202e1a5fe26c80c753071f0b573"), "app_secret");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeFacebook, fbConfigDict);

    //Twitter
    Dictionary *twConfigDict = Dictionary::create();
    twConfigDict -> setObject(String::create("mnTGqtXk0TYMXYTN7qUxg"), "consumer_key");
    twConfigDict -> setObject(String::create("ROkFqr8c3m1HXqS3rm3TJ0WkAJuwBOSaWhPbZ9Ojuc"), "consumer_secret");
    twConfigDict -> setObject(String::create("http://www.sharesdk.cn"), "redirect_uri");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeTwitter, twConfigDict);

    //Google+
    Dictionary *gpConfigDict = Dictionary::create();
    gpConfigDict -> setObject(String::create("232554794995.apps.googleusercontent.com"), "client_id");
    gpConfigDict -> setObject(String::create("PEdFgtrMw97aCvf0joQj7EMk"), "client_secret");
    gpConfigDict -> setObject(String::create("http://localhost"), "redirect_uri");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeGooglePlus, gpConfigDict);

    //人人网
    Dictionary *rrConfigDict = Dictionary::create();
    rrConfigDict -> setObject(String::create("226427"), "app_id");
    rrConfigDict -> setObject(String::create("fc5b8aed373c4c27a05b712acba0f8c3"), "app_key");
    rrConfigDict -> setObject(String::create("f29df781abdd4f49beca5a2194676ca4"), "secret_key");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeRenren, rrConfigDict);

    //开心网
    Dictionary *kxConfigDict = Dictionary::create();
    kxConfigDict -> setObject(String::create("358443394194887cee81ff5890870c7c"), "api_key");
    kxConfigDict -> setObject(String::create("da32179d859c016169f66d90b6db2a23"), "secret_key");
    kxConfigDict -> setObject(String::create("http://www.sharesdk.cn/"), "redirect_uri");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeKaixin, kxConfigDict);

    //邮件
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeMail, NULL);

    //打印
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeAirPrint, NULL);

    //拷贝
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeCopy, NULL);

    //搜狐微博
    Dictionary *shwbConfigDict = Dictionary::create();
    shwbConfigDict -> setObject(String::create("SAfmTG1blxZY3HztESWx"), "consumer_key");
    shwbConfigDict -> setObject(String::create("yfTZf)!rVwh*3dqQuVJVsUL37!F)!yS9S!Orcsij"), "consumer_secret");
    shwbConfigDict -> setObject(String::create("http://www.sharesdk.cn"), "callback_uri");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeSohuWeibo, shwbConfigDict);

    //网易微博
    Dictionary *neConfigDict = Dictionary::create();
    neConfigDict -> setObject(String::create("T5EI7BXe13vfyDuy"), "consumer_key");
    neConfigDict -> setObject(String::create("gZxwyNOvjFYpxwwlnuizHRRtBRZ2lV1j"), "consumer_secret");
    neConfigDict -> setObject(String::create("http://www.shareSDK.cn"), "redirect_uri");
    C2DXShareSDK::setPlatformConfig(C2DXPlatType163Weibo, neConfigDict);

    //豆瓣
    Dictionary *dbConfigDict = Dictionary::create();
    dbConfigDict -> setObject(String::create("02e2cbe5ca06de5908a863b15e149b0b"), "api_key");
    dbConfigDict -> setObject(String::create("9f1e7b4f71304f2f"), "secret");
    dbConfigDict -> setObject(String::create("http://www.sharesdk.cn"), "redirect_uri");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeDouBan, dbConfigDict);

    //印象笔记
    Dictionary *enConfigDict = Dictionary::create();
    enConfigDict -> setObject(String::create("sharesdk-7807"), "consumer_key");
    enConfigDict -> setObject(String::create("d05bf86993836004"), "consumer_secret");
    enConfigDict -> setObject(String::create("0"), "host_type");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeEvernote, enConfigDict);

    //LinkedIn
    Dictionary *liConfigDict = Dictionary::create();
    liConfigDict -> setObject(String::create("ejo5ibkye3vo"), "api_key");
    liConfigDict -> setObject(String::create("cC7B2jpxITqPLZ5M"), "secret_key");
    liConfigDict -> setObject(String::create("http://sharesdk.cn"), "redirect_url");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeLinkedIn, liConfigDict);

    //Pinterest
    Dictionary *piConfigDict = Dictionary::create();
    piConfigDict -> setObject(String::create("1432928"), "client_id");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypePinterest, piConfigDict);

    //Pocket
    Dictionary *poConfigDict = Dictionary::create();
    poConfigDict -> setObject(String::create("11496-de7c8c5eb25b2c9fcdc2b627"), "consumer_key");
    poConfigDict -> setObject(String::create("pocketapp1234"), "redirect_uri");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypePocket, poConfigDict);

    //Instapaper
    Dictionary *ipConfigDict = Dictionary::create();
    ipConfigDict -> setObject(String::create("4rDJORmcOcSAZL1YpqGHRI605xUvrLbOhkJ07yO0wWrYrc61FA"), "consumer_key");
    ipConfigDict -> setObject(String::create("GNr1GespOQbrm8nvd7rlUsyRQsIo3boIbMguAl9gfpdL0aKZWe"), "consumer_secret");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeInstapaper, ipConfigDict);

    //有道云笔记
    Dictionary *ydConfigDict = Dictionary::create();
    ydConfigDict -> setObject(String::create("dcde25dca105bcc36884ed4534dab940"), "consumer_key");
    ydConfigDict -> setObject(String::create("d98217b4020e7f1874263795f44838fe"), "consumer_secret");
    ydConfigDict -> setObject(String::create("http://www.sharesdk.cn/"), "oauth_callback");
    ydConfigDict -> setObject(String::create("1"), "host_type");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeYouDaoNote, ydConfigDict);

    //搜狐随身看
    Dictionary *shkConfigDict = Dictionary::create();
    shkConfigDict -> setObject(String::create("e16680a815134504b746c86e08a19db0"), "app_key");
    shkConfigDict -> setObject(String::create("b8eec53707c3976efc91614dd16ef81c"), "app_secret");
    shkConfigDict -> setObject(String::create("http://sharesdk.cn"), "redirect_uri");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeSohuKan, shkConfigDict);

    //Flickr
    Dictionary *flickrConfigDict = Dictionary::create();
    flickrConfigDict -> setObject(String::create("33d833ee6b6fca49943363282dd313dd"), "api_key");
    flickrConfigDict -> setObject(String::create("3a2c5b42a8fbb8bb"), "api_secret");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeFlickr, flickrConfigDict);

    //Tumblr
    Dictionary *tumblrConfigDict = Dictionary::create();
    tumblrConfigDict -> setObject(String::create("2QUXqO9fcgGdtGG1FcvML6ZunIQzAEL8xY6hIaxdJnDti2DYwM"), "consumer_key");
    tumblrConfigDict -> setObject(String::create("3Rt0sPFj7u2g39mEVB3IBpOzKnM3JnTtxX2bao2JKk4VV1gtNo"), "consumer_secret");
    tumblrConfigDict -> setObject(String::create("http://sharesdk.cn"), "callback_url");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeTumblr, tumblrConfigDict);

    //Dropbox
    Dictionary *dropboxConfigDict = Dictionary::create();
    dropboxConfigDict -> setObject(String::create("7janx53ilz11gbs"), "app_key");
    dropboxConfigDict -> setObject(String::create("c1hpx5fz6tzkm32"), "app_secret");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeDropbox, dropboxConfigDict);

    //Instagram
    Dictionary *instagramConfigDict = Dictionary::create();
    instagramConfigDict -> setObject(String::create("ff68e3216b4f4f989121aa1c2962d058"), "client_id");
    instagramConfigDict -> setObject(String::create("1b2e82f110264869b3505c3fe34e31a1"), "client_secret");
    instagramConfigDict -> setObject(String::create("http://sharesdk.cn"), "redirect_uri");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeInstagram, instagramConfigDict);

    //VK
    Dictionary *vkConfigDict = Dictionary::create();
    vkConfigDict -> setObject(String::create("3921561"), "application_id");
    vkConfigDict -> setObject(String::create("6Qf883ukLDyz4OBepYF1"), "secret_key");
    C2DXShareSDK::setPlatformConfig(C2DXPlatTypeVKontakte, vkConfigDict);
}
