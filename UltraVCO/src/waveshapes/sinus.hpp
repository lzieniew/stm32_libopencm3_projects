constexpr float sinus_tab[512] = {
  255.0000,
  258.0000,
  261.0000,
  264.0000,
  268.0000,
  271.0000,
  274.0000,
  277.0000,
  280.0000,
  283.0000,
  286.0000,
  289.0000,
  292.0000,
  296.0000,
  299.0000,
  302.0000,
  305.0000,
  308.0000,
  311.0000,
  314.0000,
  317.0000,
  320.0000,
  323.0000,
  326.0000,
  329.0000,
  332.0000,
  335.0000,
  338.0000,
  341.0000,
  344.0000,
  347.0000,
  350.0000,
  353.0000,
  356.0000,
  359.0000,
  361.0000,
  364.0000,
  367.0000,
  370.0000,
  373.0000,
  375.0000,
  378.0000,
  381.0000,
  384.0000,
  386.0000,
  389.0000,
  392.0000,
  394.0000,
  397.0000,
  400.0000,
  402.0000,
  405.0000,
  407.0000,
  410.0000,
  412.0000,
  415.0000,
  417.0000,
  419.0000,
  422.0000,
  424.0000,
  427.0000,
  429.0000,
  431.0000,
  433.0000,
  436.0000,
  438.0000,
  440.0000,
  442.0000,
  444.0000,
  446.0000,
  448.0000,
  451.0000,
  453.0000,
  454.0000,
  456.0000,
  458.0000,
  460.0000,
  462.0000,
  464.0000,
  466.0000,
  467.0000,
  469.0000,
  471.0000,
  473.0000,
  474.0000,
  476.0000,
  477.0000,
  479.0000,
  480.0000,
  482.0000,
  483.0000,
  485.0000,
  486.0000,
  487.0000,
  489.0000,
  490.0000,
  491.0000,
  492.0000,
  493.0000,
  494.0000,
  496.0000,
  497.0000,
  498.0000,
  499.0000,
  499.0000,
  500.0000,
  501.0000,
  502.0000,
  503.0000,
  504.0000,
  504.0000,
  505.0000,
  506.0000,
  506.0000,
  507.0000,
  507.0000,
  508.0000,
  508.0000,
  509.0000,
  509.0000,
  509.0000,
  510.0000,
  510.0000,
  510.0000,
  510.0000,
  510.0000,
  510.0000,
  510.0000,
  511.0000,
  510.0000,
  510.0000,
  510.0000,
  510.0000,
  510.0000,
  510.0000,
  510.0000,
  509.0000,
  509.0000,
  509.0000,
  508.0000,
  508.0000,
  507.0000,
  507.0000,
  506.0000,
  506.0000,
  505.0000,
  504.0000,
  504.0000,
  503.0000,
  502.0000,
  501.0000,
  500.0000,
  499.0000,
  499.0000,
  498.0000,
  497.0000,
  496.0000,
  494.0000,
  493.0000,
  492.0000,
  491.0000,
  490.0000,
  489.0000,
  487.0000,
  486.0000,
  485.0000,
  483.0000,
  482.0000,
  480.0000,
  479.0000,
  477.0000,
  476.0000,
  474.0000,
  473.0000,
  471.0000,
  469.0000,
  467.0000,
  466.0000,
  464.0000,
  462.0000,
  460.0000,
  458.0000,
  456.0000,
  454.0000,
  453.0000,
  451.0000,
  448.0000,
  446.0000,
  444.0000,
  442.0000,
  440.0000,
  438.0000,
  436.0000,
  433.0000,
  431.0000,
  429.0000,
  427.0000,
  424.0000,
  422.0000,
  419.0000,
  417.0000,
  415.0000,
  412.0000,
  410.0000,
  407.0000,
  405.0000,
  402.0000,
  400.0000,
  397.0000,
  394.0000,
  392.0000,
  389.0000,
  386.0000,
  384.0000,
  381.0000,
  378.0000,
  375.0000,
  373.0000,
  370.0000,
  367.0000,
  364.0000,
  361.0000,
  359.0000,
  356.0000,
  353.0000,
  350.0000,
  347.0000,
  344.0000,
  341.0000,
  338.0000,
  335.0000,
  332.0000,
  329.0000,
  326.0000,
  323.0000,
  320.0000,
  317.0000,
  314.0000,
  311.0000,
  308.0000,
  305.0000,
  302.0000,
  299.0000,
  296.0000,
  292.0000,
  289.0000,
  286.0000,
  283.0000,
  280.0000,
  277.0000,
  274.0000,
  271.0000,
  268.0000,
  264.0000,
  261.0000,
  258.0000,
  255.0000,
  252.0000,
  249.0000,
  246.0000,
  242.0000,
  239.0000,
  236.0000,
  233.0000,
  230.0000,
  227.0000,
  224.0000,
  221.0000,
  218.0000,
  214.0000,
  211.0000,
  208.0000,
  205.0000,
  202.0000,
  199.0000,
  196.0000,
  193.0000,
  190.0000,
  187.0000,
  184.0000,
  181.0000,
  178.0000,
  175.0000,
  172.0000,
  169.0000,
  166.0000,
  163.0000,
  160.0000,
  157.0000,
  154.0000,
  151.0000,
  149.0000,
  146.0000,
  143.0000,
  140.0000,
  137.0000,
  135.0000,
  132.0000,
  129.0000,
  126.0000,
  124.0000,
  121.0000,
  118.0000,
  116.0000,
  113.0000,
  110.0000,
  108.0000,
  105.0000,
  103.0000,
  100.0000,
   98.0000,
   95.0000,
   93.0000,
   91.0000,
   88.0000,
   86.0000,
   83.0000,
   81.0000,
   79.0000,
   77.0000,
   74.0000,
   72.0000,
   70.0000,
   68.0000,
   66.0000,
   64.0000,
   62.0000,
   59.0000,
   57.0000,
   56.0000,
   54.0000,
   52.0000,
   50.0000,
   48.0000,
   46.0000,
   44.0000,
   43.0000,
   41.0000,
   39.0000,
   37.0000,
   36.0000,
   34.0000,
   33.0000,
   31.0000,
   30.0000,
   28.0000,
   27.0000,
   25.0000,
   24.0000,
   23.0000,
   21.0000,
   20.0000,
   19.0000,
   18.0000,
   17.0000,
   16.0000,
   14.0000,
   13.0000,
   12.0000,
   11.0000,
   11.0000,
   10.0000,
    9.0000,
    8.0000,
    7.0000,
    6.0000,
    6.0000,
    5.0000,
    4.0000,
    4.0000,
    3.0000,
    3.0000,
    2.0000,
    2.0000,
    1.0000,
    1.0000,
    1.0000,
    0.0000,
    0.0000,
    0.0000,
    0.0000,
    0.0000,
    0.0000,
    0.0000,
    0.0000,
    0.0000,
    0.0000,
    0.0000,
    0.0000,
    0.0000,
    0.0000,
    0.0000,
    1.0000,
    1.0000,
    1.0000,
    2.0000,
    2.0000,
    3.0000,
    3.0000,
    4.0000,
    4.0000,
    5.0000,
    6.0000,
    6.0000,
    7.0000,
    8.0000,
    9.0000,
   10.0000,
   11.0000,
   11.0000,
   12.0000,
   13.0000,
   14.0000,
   16.0000,
   17.0000,
   18.0000,
   19.0000,
   20.0000,
   21.0000,
   23.0000,
   24.0000,
   25.0000,
   27.0000,
   28.0000,
   30.0000,
   31.0000,
   33.0000,
   34.0000,
   36.0000,
   37.0000,
   39.0000,
   41.0000,
   43.0000,
   44.0000,
   46.0000,
   48.0000,
   50.0000,
   52.0000,
   54.0000,
   56.0000,
   57.0000,
   59.0000,
   62.0000,
   64.0000,
   66.0000,
   68.0000,
   70.0000,
   72.0000,
   74.0000,
   77.0000,
   79.0000,
   81.0000,
   83.0000,
   86.0000,
   88.0000,
   91.0000,
   93.0000,
   95.0000,
   98.0000,
  100.0000,
  103.0000,
  105.0000,
  108.0000,
  110.0000,
  113.0000,
  116.0000,
  118.0000,
  121.0000,
  124.0000,
  126.0000,
  129.0000,
  132.0000,
  135.0000,
  137.0000,
  140.0000,
  143.0000,
  146.0000,
  149.0000,
  151.0000,
  154.0000,
  157.0000,
  160.0000,
  163.0000,
  166.0000,
  169.0000,
  172.0000,
  175.0000,
  178.0000,
  181.0000,
  184.0000,
  187.0000,
  190.0000,
  193.0000,
  196.0000,
  199.0000,
  202.0000,
  205.0000,
  208.0000,
  211.0000,
  214.0000,
  218.0000,
  221.0000,
  224.0000,
  227.0000,
  230.0000,
  233.0000,
  236.0000,
  239.0000,
  242.0000,
  246.0000,
  249.0000,
  252.0000
};