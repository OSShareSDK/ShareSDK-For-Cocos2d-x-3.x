#include "HelloWorldScene.h"
#include "C2DXShareSDK.h"

USING_NS_CC;
using namespace cn::sharesdk;

void authResultHandler(C2DXResponseState state, C2DXPlatType platType, __Dictionary *error)
{
    switch (state) {
        case C2DXResponseStateSuccess:
            C2DXShareSDK::toast("授权成功");
            break;
        case C2DXResponseStateFail:
            C2DXShareSDK::toast("授权失败");
            break;
        default:
            C2DXShareSDK::toast("授权取消");
            break;
    }
}

void getUserResultHandler(C2DXResponseState state, C2DXPlatType platType, __Dictionary *userInfo, __Dictionary *error, __Dictionary *db)
{
    if (state == C2DXResponseStateSuccess)
    {
        //输出用户信息
    	static __Array*allKeys = db -> allKeys();
                    allKeys->retain();
        for (int i = 0; i < allKeys -> count(); i++)
        {
        	__String *key = (__String *)allKeys -> objectAtIndex(i);
            Ref *obj = db -> objectForKey(key -> getCString());

            CCLog("key = %s", key -> getCString());
            if (dynamic_cast<__String *>(obj))
            {
                CCLog("value = %s", dynamic_cast<__String *>(obj) -> getCString());
            }
            else if (dynamic_cast<__Integer *>(obj))
            {
                CCLog("value = %d", dynamic_cast<__Integer *>(obj) -> getValue());
            }
            else if (dynamic_cast<__Double *>(obj))
            {
                CCLog("value = %f", dynamic_cast<__Double *>(obj) -> getValue());
            }
        }
        allKeys->release();
    }
}

void shareResultHandler(C2DXResponseState state, C2DXPlatType platType, __Dictionary *shareInfo, __Dictionary *error)
{
    switch (state) {
        case C2DXResponseStateSuccess:
            C2DXShareSDK::toast("分享成功");
            break;
        case C2DXResponseStateFail:
            C2DXShareSDK::toast("分享失败");
            break;
        default:
            C2DXShareSDK::toast("分享取消");
            break;
    }
}

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // this, MenuItemLabel::create(label, std::bind(&MyClass::callback, this, std::placeholders::_1));

    //ShareSDK 菜单开始
    MenuItemLabel *shareForWechatTimeLineItem = MenuItemLabel::create(LabelTTF::create("指定平台分享", "Arial", 40),
    															this,
                                                                menu_selector(HelloWorld::shareForWechatTimeLineMenuItemClick));
    MenuItemLabel *authMenuItem = MenuItemLabel::create(LabelTTF::create("授权", "Arial", 40),
                                                            this,
                                                            menu_selector(HelloWorld::authMenuItemClick));
    MenuItemLabel *cancelAuthMenuItem = MenuItemLabel::create(LabelTTF::create("取消授权", "Arial", 40),
                                                                  this,
                                                                  menu_selector(HelloWorld::cancelAuthMenuItemClick));
    MenuItemLabel *hasAuthMenuItem = MenuItemLabel::create(LabelTTF::create("是否授权", "Arial", 40),
                                                               this,
                                                               menu_selector(HelloWorld::hasAuthMenuItemClick));
    MenuItemLabel *getUserMenuItem = MenuItemLabel::create(LabelTTF::create("用户信息", "Arial", 40),
                                                               this,
                                                               menu_selector(HelloWorld::getUserInfoMenuItemClick));
    MenuItemLabel *shareMenuItem = MenuItemLabel::create(LabelTTF::create("分享", "Arial", 40),
                                                             this,
                                                             menu_selector(HelloWorld::shareMenuItemClick));

    Menu *itemsMenu = Menu::create(shareForWechatTimeLineItem, authMenuItem, cancelAuthMenuItem, hasAuthMenuItem, getUserMenuItem, shareMenuItem, (MenuItemLabel*)NULL);
    itemsMenu -> alignItemsHorizontallyWithPadding(20);
    itemsMenu -> setPosition(Point(Director::getInstance() -> getWinSize().width / 2, 100));
    this -> addChild(itemsMenu);
    //ShareSDK 菜单结束

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, (MenuItemImage*)NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void HelloWorld::authMenuItemClick(cocos2d::Ref* pSender)
{
    C2DXShareSDK::authorize(C2DXPlatTypeSinaWeibo, authResultHandler);
}

void HelloWorld::cancelAuthMenuItemClick(cocos2d::Ref* pSender)
{
    C2DXShareSDK::cancelAuthorize(C2DXPlatTypeSinaWeibo);
}

void HelloWorld::hasAuthMenuItemClick(cocos2d::Ref* pSender)
{
    if (C2DXShareSDK::hasAutorized(C2DXPlatTypeSinaWeibo))
    {
        C2DXShareSDK::toast("用户已授权");
    }
    else
    {
        C2DXShareSDK::toast("用户尚未授权");
    }
}

void HelloWorld::getUserInfoMenuItemClick(cocos2d::Ref* pSender)
{
    C2DXShareSDK::getUserInfo(C2DXPlatTypeQQ, getUserResultHandler);
}

void HelloWorld::shareForWechatTimeLineMenuItemClick(cocos2d::Ref* pSender)
{
	__Dictionary *content = __Dictionary::create();
	//Dictionary可用的Key如下，如果需要用到其它字段，可自行参考Sample中的代码实现：
	// (并不是所有平台都有这些字段，需要参考文档http://wiki.mob.com/Android_%E4%B8%8D%E5%90%8C%E5%B9%B3%E5%8F%B0%E5%88%86%E4%BA%AB%E5%86%85%E5%AE%B9%E7%9A%84%E8%AF%A6%E7%BB%86%E8%AF%B4%E6%98%8E
	content -> setObject(String::create("jajax"), "content"); //要分享的内容，注意在文档中content对应的是text字段
	//content -> setObject(String::create("http://img0.bdstatic.com/img/image/shouye/systsy-11927417755.jpg"), "image"); //可以是本地路径（如：/sdcard/a.jpg）或是一个URL
	//content -> setObject(String::create("for title"), "title");
	//content -> setObject(String::create("http://sharesdk.cn"), "url");
	//content -> setObject(String::createWithFormat("%d", C2DXContentTypeImage), "type");
	C2DXShareSDK::shareContent(C2DXPlatTypeSinaWeibo , content , false, shareResultHandler);
}

void HelloWorld::shareMenuItemClick(cocos2d::Ref * pSender)
{
	__Dictionary *content = __Dictionary::create();
    //Dictionary可用的Key如下，如果需要用到其它字段，可自行参考Sample中的代码实现：
    // (并不是所有平台都有这些字段，需要参考文档http://wiki.mob.com/Android_%E4%B8%8D%E5%90%8C%E5%B9%B3%E5%8F%B0%E5%88%86%E4%BA%AB%E5%86%85%E5%AE%B9%E7%9A%84%E8%AF%A6%E7%BB%86%E8%AF%B4%E6%98%8E)

    content -> setObject(String::create("jaja"), "content"); //要分享的内容，注意在文档中content对应的是text字段
    content -> setObject(String::create("http://img0.bdstatic.com/img/image/shouye/systsy-11927417755.jpg"), "image"); //可以是本地路径（如：/sdcard/a.jpg）或是一个URL
    content -> setObject(String::create("for title"), "title");
    content -> setObject(String::create("测试描述"), "description");
    content -> setObject(String::create("http://sharesdk.cn"), "url");
    content -> setObject(String::createWithFormat("%d", C2DXContentTypeNews), "type");
    content -> setObject(String::create("http://sharesdk.cn"), "siteUrl");
    content -> setObject(String::create("ShareSDK"), "site");
    content -> setObject(String::create("http://mp3.mwap8.com/destdir/Music/2009/20090601/ZuiXuanMinZuFeng20090601119.mp3"), "musicUrl");
    content -> setObject(String::create("extInfo"), "extInfo"); //微信分享应用时传给应用的附加信息
    C2DXShareSDK::showShareMenu(NULL, content, cocos2d::Point(100, 100), C2DXMenuArrowDirectionLeft, shareResultHandler);
//    C2DXShareSDK::showShareView(C2DXPlatTypeSinaWeibo, content, shareResultHandler);
}
