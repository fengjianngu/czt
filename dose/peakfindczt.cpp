//
// File: peakfindczt.cpp
//
// MATLAB Coder version            : 3.0
// C/C++ source code generated on  : 05-Sep-2018 09:52:22
//

// Include Files
#include "rt_nonfinite.h"
#include "peakfindczt.h"

// Function Declarations
static float b_erfc(float x);
static void bgStrip_SNIP(const float spe[4096], float spe_stripped[4096]);
static void rdivide(const float x[4096], const float y[4096], float z[4096]);
static double rt_powd_snf(double u0, double u1);
static float sum(const float x[91]);

// Function Definitions

//
// Arguments    : float x
// Return Type  : float
//
static float b_erfc(float x)
{
  double absx;
  double s;
  double S;
  double R;
  int eint;

  // ========================== COPYRIGHT NOTICE ============================
  //  The algorithms for calculating ERF(X) and ERFC(X) are derived
  //  from FDLIBM, which has the following notice:
  //
  //  Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
  //
  //  Developed at SunSoft, a Sun Microsystems, Inc. business.
  //  Permission to use, copy, modify, and distribute this
  //  software is freely granted, provided that this notice
  //  is preserved.
  // =============================    END    ================================
  absx = fabs((double)x);
  if (rtIsNaN((double)x)) {
    s = x;
  } else if (rtIsInf((double)x)) {
    if (x < 0.0F) {
      s = 2.0;
    } else {
      s = 0.0;
    }
  } else if (absx < 0.84375) {
    if (absx < 1.3877787807814457E-17) {
      s = 1.0 - x;
    } else {
      s = (double)x * x;
      s = (0.12837916709551256 + s * (-0.3250421072470015 + s *
            (-0.02848174957559851 + s * (-0.0057702702964894416 + s *
              -2.3763016656650163E-5)))) / (1.0 + s * (0.39791722395915535 + s *
        (0.0650222499887673 + s * (0.0050813062818757656 + s *
        (0.00013249473800432164 + s * -3.9602282787753681E-6)))));
      if (x < 0.25F) {
        s = 1.0 - (x + x * s);
      } else {
        s = 0.5 - (x * s + (x - 0.5));
      }
    }
  } else if (absx < 1.25) {
    S = -0.0023621185607526594 + (absx - 1.0) * (0.41485611868374833 + (absx -
      1.0) * (-0.37220787603570132 + (absx - 1.0) * (0.31834661990116175 + (absx
      - 1.0) * (-0.11089469428239668 + (absx - 1.0) * (0.035478304325618236 +
      (absx - 1.0) * -0.0021663755948687908)))));
    s = 1.0 + (absx - 1.0) * (0.10642088040084423 + (absx - 1.0) *
      (0.540397917702171 + (absx - 1.0) * (0.071828654414196266 + (absx - 1.0) *
      (0.12617121980876164 + (absx - 1.0) * (0.013637083912029051 + (absx - 1.0)
      * 0.011984499846799107)))));
    if (x >= 0.0F) {
      s = 0.15493708848953247 - S / s;
    } else {
      s = 1.0 + (0.84506291151046753 + S / s);
    }
  } else if (x < -6.0F) {
    s = 2.0;
  } else if (x >= 28.0F) {
    s = 0.0;
  } else {
    s = 1.0 / (absx * absx);
    if (absx < 2.8571414947509766) {
      R = -0.0098649440348471482 + s * (-0.69385857270718176 + s *
        (-10.558626225323291 + s * (-62.375332450326006 + s *
        (-162.39666946257347 + s * (-184.60509290671104 + s * (-81.2874355063066
        + s * -9.8143293441691455))))));
      S = 1.0 + s * (19.651271667439257 + s * (137.65775414351904 + s *
        (434.56587747522923 + s * (645.38727173326788 + s * (429.00814002756783
        + s * (108.63500554177944 + s * (6.5702497703192817 + s *
        -0.0604244152148581)))))));
    } else {
      R = -0.0098649429247001 + s * (-0.799283237680523 + s *
        (-17.757954917754752 + s * (-160.63638485582192 + s *
        (-637.56644336838963 + s * (-1025.0951316110772 + s * -483.5191916086514)))));
      S = 1.0 + s * (30.338060743482458 + s * (325.79251299657392 + s *
        (1536.729586084437 + s * (3199.8582195085955 + s * (2553.0504064331644 +
        s * (474.52854120695537 + s * -22.440952446585818))))));
    }

    if ((!rtIsInf(absx)) && (!rtIsNaN(absx))) {
      s = frexp(absx, &eint);
    } else {
      s = absx;
      eint = 0;
    }

    s = floor(s * 2.097152E+6) / 2.097152E+6 * rt_powd_snf(2.0, (double)eint);
    s = exp(-s * s - 0.5625) * exp((s - absx) * (s + absx) + R / S) / absx;
    if (x < 0.0F) {
      s = 2.0 - s;
    }
  }

  return (float)s;
}

//
// ------------------------------------------------------------------------
//  ������bgStrip_SNIP
//  ����ʹ��SNIP�㷨ʵ��gamma���׵�ȫ�����׵��Զ��۳�
//        SNIP:Sensitive Nonlinear Iterative Peak Algorithms
//  �������̽����õ���gamma���� spe�������� m
//  �����׿۳���gamma���� spe_stripped
//  ------------------------------------------------------------------------
//  REVISE HISTROY
//  2014.06.06  |  first version
//  ------------------------------------------------------------------------
// Arguments    : const float spe[4096]
//                float spe_stripped[4096]
// Return Type  : void
//
static void bgStrip_SNIP(const float spe[4096], float spe_stripped[4096])
{
  float v[4096];
  float w[4096];
  int i;
  int p;
  int i1;
  int b_i;
  float a2;
  float x;
  float b_spe_stripped;

  // subtracts background from detected spectrum Y by SNIP algorithm
  // 'bgStrip_SNIP:13' N = length(spe) ;
  // 'bgStrip_SNIP:14' v = zeros(N,1) ;
  // 'bgStrip_SNIP:15' w = zeros(N,1) ;
  // 'bgStrip_SNIP:16' bg = zeros(N,1) ;
  // 'bgStrip_SNIP:17' spe_stripped = zeros(N,1) ;
  // 'bgStrip_SNIP:18' spe = double(spe) ;
  // --------------------1.�������������ݽ���LLS�任-------------------------- 
  // ��Ȼ���������ڴ���߼����׷巽���������,��ƽ�����������ǿ����ֱȽ���Խ 
  // 'bgStrip_SNIP:21' for i=1:N
  for (i = 0; i < 4096; i++) {
    w[i] = 0.0F;

    // 'bgStrip_SNIP:22' v( i)=log(log(sqrt(spe(i)+1)+1)+1);
    v[i] = (float)log((double)((float)log((double)((float)sqrt((double)(spe[i] +
      1.0F)) + 1.0F)) + 1.0F));

    // LLS�任
  }

  // ------------------2.�Ա任�����ݽ���ȫ�ױ��׿۳�-------------------------- 
  // SNIP��̣�mΪ�ܵ�����pΪ��p�ε����p�ε���е�i��� v(i)pֵȷ����ʽ�� 
  // ͨ��Ƚ�v(i)��v(i+p)��v(i-p)��ƽ��ֵ�Ĵ�С,��ȡ����е���Сֵ��  
  // 'bgStrip_SNIP:28' for p=1:m
  for (p = 0; p < 30; p++) {
    //  SNIP��̡�
    // 'bgStrip_SNIP:29' for i=p+1:N-p
    i1 = (-p - p) + 4093;
    for (i = 0; i <= i1; i++) {
      b_i = (p + i) + 1;

      // 'bgStrip_SNIP:30' a1=v(i);
      // 'bgStrip_SNIP:31' a2=(v(i-p)+v(i+p)) /2;
      a2 = (v[(b_i - p) - 1] + v[(b_i + p) + 1]) / 2.0F;

      // 'bgStrip_SNIP:32' if a1>a2
      if (v[b_i] > a2) {
        // ȡ����е�Сֵ������
        // 'bgStrip_SNIP:33' w(i)=a2;
        w[b_i] = a2;
      } else {
        // 'bgStrip_SNIP:34' else
        // 'bgStrip_SNIP:35' w(i)=a1;
        w[b_i] = v[b_i];
      }
    }

    // 'bgStrip_SNIP:38' for i=p+1:N-p
    i1 = (-p - p) + 4093;
    for (i = 0; i <= i1; i++) {
      b_i = (p + i) + 1;

      // 'bgStrip_SNIP:39' v(i)=w(i);
      v[b_i] = w[b_i];

      // wд�ص�v�С�
    }
  }

  // %----------------3.��SNIP�任�������ݽ���LLS���任----------------------- 
  // 'bgStrip_SNIP:44' for i=1:N
  // --------------------4.����ȫ�׿۳�׺�ľ�������-------------------------- 
  // 'bgStrip_SNIP:49' for i=1:N
  for (i = 0; i < 4096; i++) {
    //  LLS��任
    // 'bgStrip_SNIP:45' bg(i)=(exp(exp(v(i))-1)-1)^2-1;
    x = (float)exp((double)((float)exp((double)v[i]) - 1.0F));

    // ����ȫ�׵ľ�������
    // 'bgStrip_SNIP:50' spe_stripped(i)=spe(i)-bg( i);
    b_spe_stripped = spe[i] - ((x - 1.0F) * (x - 1.0F) - 1.0F);

    // 'bgStrip_SNIP:51' if spe_stripped(i) < 0
    if (b_spe_stripped < 0.0F) {
      // 'bgStrip_SNIP:52' spe_stripped(i)  = -spe_stripped(i);
      b_spe_stripped = -b_spe_stripped;
    }

    spe_stripped[i] = b_spe_stripped;
  }
}

//
// Arguments    : const float x[4096]
//                const float y[4096]
//                float z[4096]
// Return Type  : void
//
static void rdivide(const float x[4096], const float y[4096], float z[4096])
{
  int i;
  for (i = 0; i < 4096; i++) {
    z[i] = x[i] / y[i];
  }
}

//
// Arguments    : double u0
//                double u1
// Return Type  : double
//
static double rt_powd_snf(double u0, double u1)
{
  double y;
  double d0;
  double d1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    d0 = fabs(u0);
    d1 = fabs(u1);
    if (rtIsInf(u1)) {
      if (d0 == 1.0) {
        y = rtNaN;
      } else if (d0 > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

//
// Arguments    : const float x[91]
// Return Type  : float
//
static float sum(const float x[91])
{
  float y;
  int k;
  y = x[0];
  for (k = 0; k < 90; k++) {
    y += x[k + 1];
  }

  return y;
}

//
// 1. smooth the spe input
// Arguments    : const float spe[4096]
//                float peakm[100]
// Return Type  : void
//
void peakfindczt(const float spe[4096], float peakm[100])
{
  float speSmoothed[4096];
  int i;
  float b_speSmoothed;
  float speStripped[4096];
  float G[91];
  int j;
  float b_G;
  float c_G[91];
  float fcnOutput;
  int i0;
  float data_trans[4096];
  float ddata_trans[4096];
  float b_j;

  // 'peakfindczt:3' span = 17 ;
  // 'peakfindczt:4' order = 3 ;
  // 'peakfindczt:5' speSmoothed = sgsmooth(spe,span,order);
  // This is a program for smoothing the analytical signals.x can be a matrix
  // with every column being an analytical signal vector.
  // The parameter win_num is the window size which can be chosen to have a
  // value of 7 to 17,say 7 9 11 13 15 17; The parameter poly_order is the
  // polynomiar order which can be chosen to have a value of 2 or 3, and 4 or5.
  // 'sgsmooth:7' [m1,n1]=size(x);
  // 'sgsmooth:8' y=zeros(size(x));
  memset(&speSmoothed[0], 0, sizeof(float) << 12);

  // 'sgsmooth:9' if win_num==7
  // 'sgsmooth:90' elseif win_num==17
  // 'sgsmooth:91' if poly_order==2 || poly_order==3
  // 'sgsmooth:92' coef1=[-21 -6 7 18 27 34 39 42 43 42 39 34 27 18 7 -6 -21]/323; 
  // 'sgsmooth:93' for j=1:n1
  // 'sgsmooth:94' for i=9:m1-8
  for (i = 0; i < 4080; i++) {
    // 'sgsmooth:95' y(i,j)=coef1(1)*x(i-8,j)+coef1(2)*x(i-7,j)+coef1(3)*x(i-6,j)+coef1(4)*x(i-5,j)+coef1(5)*x(i-4,j)+coef1(6)*x(i-3,j)+coef1(7)*x(i-2,j)+coef1(8)*x(i-1,j)+coef1(9)*x(i,j)+coef1(10)*x(i+1,j)+coef1(11)*x(i+2,j)+coef1(12)*x(i+3,j)+coef1(13)*x(i+4,j)+coef1(14)*x(i+5,j)+coef1(15)*x(i+6,j)+coef1(16)*x(i+7,j)+coef1(17)*x(i+8,j); 
    speSmoothed[i + 8] = (((((((((((((((-0.0650154799F * spe[i] + -0.0185758509F
      * spe[1 + i]) + 0.021671826F * spe[i + 2]) + 0.0557275526F * spe[3 + i]) +
      0.0835913345F * spe[4 + i]) + 0.105263159F * spe[5 + i]) + 0.120743036F *
      spe[6 + i]) + 0.13003096F * spe[7 + i]) + 0.133126929F * spe[i + 8]) +
      0.13003096F * spe[9 + i]) + 0.120743036F * spe[10 + i]) + 0.105263159F *
      spe[11 + i]) + 0.0835913345F * spe[12 + i]) + 0.0557275526F * spe[13 + i])
      + 0.021671826F * spe[14 + i]) + -0.0185758509F * spe[15 + i]) +
      -0.0650154799F * spe[16 + i];
  }

  // 'sgsmooth:106' y(y<0)=0 ;
  for (i = 0; i < 4096; i++) {
    b_speSmoothed = speSmoothed[i];
    if (speSmoothed[i] < 0.0F) {
      b_speSmoothed = 0.0F;
    }

    speSmoothed[i] = b_speSmoothed;
  }

  //  speSmoothed = smooth(spe,span,'sgolay',1);
  // 2.  strip
  // 'peakfindczt:8' niter = 30 ;
  // 'peakfindczt:9' speStripped = bgStrip_SNIP(speSmoothed,niter) ;
  bgStrip_SNIP(speSmoothed, speStripped);

  // 3. peaksearch
  // 'peakfindczt:11' threshold = 10 ;
  // 'peakfindczt:12' halfwidth = 30 ;
  // 'peakfindczt:13' [ ~, ~, peakm ] = symoarea(speStripped,threshold,halfwidth); 
  //  ------------------------------------------------------------------------
  //  函数名：symoarea (short for Symmetrical 0 area method)
  //  描述：使用对称零面积法进行峰的几何参数计算，包括峰位峰区 
  //  输入参数： 能谱数据data(建议使用平滑后能谱）
  //            峰判定变量阈值threshold
  //            测量能量峰半宽度H
  //            变换窗宽度W=2m+1
  //  输出函数： 峰区左边界lm,右边界rm
  //            峰位置peakm
  //  ------------------------------------------------------------------------
  // tb=1300;%变换开始位置
  // m=100;%变宽宽度2m+1,也即是窗宽度
  // H=50;%初始定义一个半宽宽
  // threshold=4;
  // 该函数使用对称零面积法进行峰的几何参数计算
  // 'symoarea:17' peakm=zeros(100,1);
  memset(&peakm[0], 0, 100U * sizeof(float));

  // -----------1.利用较大窗宽度初步寻峰W=3H，估计重峰的可能性----------------- 
  // 'symoarea:20' m=round(1.5*H);
  // 此时m为1.5H四舍五入取整
  // 1.1构造对称零面积窗函数G
  // 初始化对称零面积窗函数中间函数Gtmp
  // 'symoarea:23' SP=zeros(2*m+1,1);
  // 'symoarea:24' G=zeros(2*m+1,1);
  // 'symoarea:25' T=zeros(2*m+1,1);
  //  for j=1:2*m+1
  //      SP(j)=exp(-4*log(2)*(((j-m-1)/H)^2));
  //  end
  // 'symoarea:30' m = round(1.5*H) ;
  // 'symoarea:31' Hg = 1;
  // 'symoarea:32' sigma = H/3 ;
  // 'symoarea:33' Ht = 0.4 ;
  // 'symoarea:34' Ts = 2 ;
  // 'symoarea:35' for j=1:2*m+1
  // 'symoarea:39' SP = G+T ;
  // 对Gtmp求和得到d
  // 'symoarea:42' d=sum(SP/(2*m+1));
  for (j = 0; j < 91; j++) {
    // 'symoarea:36' G(j)=Hg*exp(-(j-(m+1))^2/(2*sigma^2)) ;
    // 'symoarea:37' T(j)=Hg*Ht*exp((j-(m+1))/(Ts*sigma))*erfc((j-(m+1))/(sqrt(2)*sigma)+1/(sqrt(2)*Ts)) ; 
    b_G = (float)exp((double)((float)-((j - 45) * (j - 45)) / 200.0F)) + 0.4F *
      (float)exp((double)(((1.0F + (float)j) - 46.0F) / 20.0F)) * b_erfc(((1.0F
      + (float)j) - 46.0F) / 14.1421356F + 0.353553385F);
    G[j] = b_G / 91.0F;
    c_G[j] = b_G;
  }

  fcnOutput = sum(G);

  // 'symoarea:43' G=SP-d;
  for (i0 = 0; i0 < 91; i0++) {
    c_G[i0] -= fcnOutput;
  }

  // 1.2将能谱数据与窗函数进行卷积运算，得到卷积后变换谱data_trans 
  // 'symoarea:46' data_trans=zeros(length(data),1);
  memset(&data_trans[0], 0, sizeof(float) << 12);

  // 'symoarea:47' for i=m+1:length(data)-m
  for (i = 0; i < 4006; i++) {
    // 'symoarea:48' for j=1:2*m+1
    for (j = 0; j < 91; j++) {
      // 'symoarea:49' data_trans(i)=data_trans(i)+G(j)*data(i+j-m-1);
      data_trans[i + 45] += c_G[j] * speStripped[i + j];
    }
  }

  // plot(data_trans);
  // 1.3计算变换谱标准偏差ddata_trans
  // 'symoarea:55' ddata_trans=zeros(length(data),1);
  memset(&ddata_trans[0], 0, sizeof(float) << 12);

  // 'symoarea:56' for i=m+1:length(data)-m
  for (i = 0; i < 4006; i++) {
    // 'symoarea:57' for j=1:2*m+1
    for (j = 0; j < 91; j++) {
      // 'symoarea:58' ddata_trans(i)=sqrt(ddata_trans(i)^2+(G(j))^2*data(i+j-m-1)); 
      ddata_trans[i + 45] = (float)sqrt((double)(ddata_trans[i + 45] *
        ddata_trans[i + 45] + c_G[j] * c_G[j] * speStripped[i + j]));
    }
  }

  // 1.4计算峰判定变量P
  // 'symoarea:63' P=data_trans./ddata_trans;
  rdivide(data_trans, ddata_trans, speSmoothed);

  // 'symoarea:64' j=1 ;
  b_j = 1.0F;

  // 1.5根据判定变量P的阈值判断峰位，保存在peakm数组中
  // 'symoarea:66' for i=2:length(data_trans)-1
  for (i = 0; i < 4094; i++) {
    // 'symoarea:67' if P(i)>threshold && P(i)>P(i-1) && P(i)>P(i+1)
    if ((speSmoothed[i + 1] > 10.0F) && (speSmoothed[i + 1] > speSmoothed[i]) &&
        (speSmoothed[i + 1] > speSmoothed[2 + i])) {
      //          if isempty(peakm)
      //              peakm(1)=i;
      //          else
      //              peakm(end+1)=i;
      //          end
      // 'symoarea:73' peakm(j)=i;
      peakm[(int)b_j - 1] = 2.0F + (float)i;

      // 'symoarea:74' j=j+1 ;
      b_j++;
    }
  }

  // -------------------------2.峰区计算和重峰判断----------------------------- 
  // 2.1 找峰位最相邻的过零点lm,rm作为峰区
  // 'symoarea:80' j=0;
  // 根据最近极点计算峰区
  // 'symoarea:82' lm=zeros(size(peakm));
  // 'symoarea:83' rm=zeros(size(peakm));
  // 'symoarea:84' for i=1:size(peakm,2)
  // 'symoarea:85' while P(peakm(i)-j-1) < P(peakm(i)-j)
  // 'symoarea:88' lm(i)=peakm(i)-j;
  // 'symoarea:89' j=0;
  // 'symoarea:90' while P(peakm(i)+j+1) < P(peakm(i)+j)
  // 'symoarea:93' rm(i)=peakm(i)+j;
  // 'symoarea:94' j=0;
  // 判断重峰
  // 'symoarea:97' multiPeakflag = zeros(size(peakm)) ;
  // 'symoarea:98' for i=1:length(peakm)
  //  peakm(multiPeakflag==1) = [] ;
  //  lm(multiPeakflag==1) = [] ;
  //  rm(multiPeakflag==1) = [] ;
  // %-----------------------测试代码及中间结果显示------------------------------ 
  //  peakm
  //  multiPeakflag
  //  figure
  //  plot(data);
  //  hold on;
  //  % plot(data_trans,'k')
  //  plot(P,'y');% judge vector
  //  %画出峰位
  //  for i=1:size(peakm,2)
  //      plot(peakm(i),data(peakm(i)),'r*');
  //      plot([lm(i),lm(i)],[0,data(lm(i))],'r');
  //      plot([rm(i),rm(i)],[0,data(rm(i))],'r');
  //      plot([lm(i),rm(i)],[data(lm(i)),data(rm(i))],'r');
  //  end
  //  hold off;
  //  title('result of peak search')
  // 画出峰区
  // 'peakfindczt:13' ~
  // 'peakfindczt:13' ~
}

//
// Arguments    : void
// Return Type  : void
//
void peakfindczt_initialize()
{
  rt_InitInfAndNaN(8U);
}

//
// Arguments    : void
// Return Type  : void
//
void peakfindczt_terminate()
{
  // (no terminate code required)
}

//
// File trailer for peakfindczt.cpp
//
// [EOF]
//
