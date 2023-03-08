### 基本功能部分

<img src="D:\ComputerScience\cs_2020_Fall_EduC-Lang\snakeProject\Game.png" style="zoom:50%;" />

#### 1.文件开头规则说明

程序运行后,开始介绍规则

```plaintext
欢迎来到贪吃蛇小游戏
你可以使用键位 "↑.↓.←.→" 或者 "W.S.A.D" 来移动蛇
F1"加速  "F2"减速  "Space"暂停
不要让蛇咬到自己或者撞到墙
现在小蛇已经准备就绪
	
```

输入

`键位“Enter”或空格可以加快读取时间`

等待5秒后开始游戏

#### 2.创建围墙并显示（一共四张地图，下只显示其中的一张）

#### 3.初始化生成蛇

```
                                        █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █     
                                        █                                       █     
                                        █                                       █     
                                        █                                       █
                                        █                                       █    
                                        █                                       █
                                        █                             █         █     
                                        █                             █         █                                                                   █                             █         █
                                        █                             █         █     
                                        █                             █         █                                                                   █                                       █
                                        █                                       █
                                        █                                       █
                                        █                                       █
                                        █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █
```



#### 4.初始化生成食物（食物不能出现在蛇身）

```c
                                    █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █     
                                    █                                       █     
                                    █                                       █     
                                    █         ⊙                            █
                                    █                                       █    
                                    █                                       █
                                    █                             █         █     
                                    █                             █         █                                                                   █                             █         █
                                    █                             █         █     
                                    █                             █         █                                                                   █                                       █
                                    █                                       █
                                    █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █
```

#### 5.控制蛇的移动（注意事项：蛇不能回头）

输入

```plaintext
按键  "↑.↓.←.→" 或者 "W.S.A.D" 来移动蛇
比如输入键位“←”
```

输出

```plaintext
                                    █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █     
                                    █                                       █     
                                    █                                       █     
                                    █         ⊙                            █
                                    █                                       █    
                                    █                                       █
                                    █                                       █     
                                    █                           █ █         █                                                                   █                             █         █
                                    █                             █         █     
                                    █                             █         █                                                                   █                                       █
                                    █                                       █
                                    █                                       █
                                    █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █

```



#### 6.吃食物加长蛇

当蛇吃到食物时，加长，并重新随机生成食物

```plaintext
                                    █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █     
                                    █                                       █     
                                    █                                       █     
                                    █          █ █ █ █ █ █ █                █
                                    █                                       █    
                                    █                                       █
                                    █                                       █     
                                    █                                       █                                                                   █                                       █
                                    █                                       █     
                                    █                                       █                                                                   █                                       █
                                    █                    ⊙                 █
                                    █                                       █
                                    █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █ █
```

#### 7.吃到自己或撞墙游戏结束

显示游戏结束，并询问玩家是否继续

                                                   游戏结束
     
                                                    你输了
    
                                                  你最终的分数是 10



                                                  是否重新开始游戏？
    
                                               输入YES继续     或者输入NO退出

#### 8.显示分数

##### 每一关存在目标分数，吃到食物可以得分，达到目标分数可以进入下一个关卡

随着得分的增加，蛇移动的速度也会增加，逐渐加大游戏难度



                                             总分：
                                            每个食物得分：10
                                            目标分数 ：250
                                        
                                             游戏规则
                                            不能穿墙，不能咬到自己
                                            用↑.↓.←.→ 或者 W.S.A.D分别控制蛇的移动.
                                            F1:加速   F2:减速
                                            ESC:退出游戏  SPACE：暂停游戏.


#### 9.使蛇加速减速暂停退出

输入

```
F1"加速  "F2"减速  "Space"暂停
```

加速会提高每个食物的得分

暂停使游戏暂时中止