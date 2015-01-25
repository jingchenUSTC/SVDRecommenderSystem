# SVDRecommenderSystem
将SVD应用于推荐系统中的评分预测问题
关于SVD的原理分析可以参见我的博客[奇异值分解(SVD)原理详解及推导](http://blog.csdn.net/zhongkejingwang/article/details/43053513)
关于代码中的SVD算法的推导可以看这里[SVD在推荐系统中的应用详解以及算法推导](http://blog.csdn.net/zhongkejingwang/article/details/43083603)
##RSVD预测公式：
![](https://github.com/jingchenUSTC/SVDRecommenderSystem/blob/master/exps/RSVD.png)
##ASVD预测公式：
![](https://github.com/jingchenUSTC/SVDRecommenderSystem/blob/master/exps/ASVD.png)
##SVD++预测公式：
![](https://github.com/jingchenUSTC/SVDRecommenderSystem/blob/master/exps/SVDPP.png)
<br>通过“isTranspose”变量设置R矩阵是否转置，转置后得到原始算法的对偶算法
##对偶ASVD预测公式：
![](https://github.com/jingchenUSTC/SVDRecommenderSystem/blob/master/exps/TASVD.png)
##对偶SVD++预测公式：
![](https://github.com/jingchenUSTC/SVDRecommenderSystem/blob/master/exps/TSVDPP.png)
