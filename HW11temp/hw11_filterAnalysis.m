clc,clear
a  = fir1(2,0.071);
A1 = a(1)+a(3)
A2 = a(2)
freqz([A1,A2])
data1 = [  0  -13401 -14969.50 -14755.20 -14652.50
  1  -11920 -14099.50 -13198.25 -14277.99
  2  -11789 -13020.00 -11902.07 -13936.39
  3  -12817 -12481.75 -11929.73 -13782.81
  4  -14643 -12792.25 -13066.98 -13899.87
  5  -15913 -13790.50 -14816.86 -14174.72
  6  -15772 -14786.25 -15893.70 -14392.77
  7  -16110 -15609.50 -15818.27 -14627.19
  8  -16585 -16095.00 -16175.03 -14895.05
  9  -15836 -16075.75 -16482.46 -15023.82
 10  -15312 -15960.75 -15764.26 -15062.56
 11  -13988 -15430.25 -15130.74 -14914.97
 12  -13865 -14750.25 -13971.16 -14770.39
 13  -13924 -14272.25 -13873.08 -14654.18
 14  -14363 -14035.00 -13984.10 -14614.16
 15  -14995 -14286.75 -14449.52 -14666.16
 16  -14666 -14487.00 -14949.96 -14666.00
 17  -15941 -14991.25 -14840.55 -14840.55
 18  -14784 -15096.50 -15782.61 -14832.33
 19  -15752 -15285.75 -14916.52 -14957.95
 20  -16463 -15735.00 -15849.34 -15163.17
 21  -16089 -15772.00 -16411.80 -15289.77
 22  -16433 -16184.25 -16136.09 -15445.61
 23  -16184 -16292.25 -16398.91 -15546.17
 24  -16233 -16234.75 -16190.71 -15640.05
 25  -15884 -16183.50 -16185.22 -15673.40
 26  -14989 -15822.50 -15761.47 -15579.36
 27  -13685 -15197.75 -14810.48 -15319.71
 28  -13323 -14470.25 -13635.44 -15045.75
 29  -13208 -13801.25 -13307.26 -14793.51
 30  -13070 -13321.50 -13189.11 -14557.12
 31  -14096 -13424.25 -13210.46 -14493.89
 32  -14321 -13673.75 -14126.80 -14469.45
 33  -14616 -14025.75 -14361.39 -14489.12
 34  -14681 -14428.50 -14624.90 -14515.29
 35  -15564 -14795.50 -14801.88 -14658.61
 36  -15509 -15092.50 -15556.47 -14774.50
 37  -15336 -15272.50 -15485.32 -14850.94
 38  -15407 -15454.00 -15345.72 -14926.25
 39  -16442 -15673.50 -15548.69 -15133.54
 40  -11065 -14562.50 -15705.89 -14576.09
 41  -16031 -14736.25 -11744.84 -14775.19
 42  -15408 -14736.50 -15945.71 -14861.66
 43  -14560 -14266.00 -15291.91 -14819.79
 44  -14385 -15096.00 -14536.04 -14759.58
 45  -13989 -14585.50 -14330.79 -14653.59
 46  -14114 -14262.00 -14006.11 -14579.21
 47  -14227 -14178.75 -14129.47 -14530.81
 48  -14520 -14212.50 -14267.11 -14528.63
 49  -14638 -14374.75 -14536.15 -14543.06
 50  -15120 -14626.25 -14703.99 -14621.99
 51  -15391 -14917.25 -15157.10 -14726.41
 52  -16052 -15300.25 -15481.49 -14907.53
 53  -15096 -15414.75 -15921.12 -14932.87
 54  -14141 -15170.00 -14965.26 -14823.71
 55  -14060 -14837.25 -14129.91 -14718.54
 56  -13814 -14277.75 -14026.32 -14594.24
 57  -13256 -13817.75 -13737.61 -14410.83
 58  -13848 -13744.50 -13337.04 -14333.06
 59  -13928 -13711.50 -13858.95 -14277.56
 60  -13921 -13738.25 -13927.04 -14228.26
 61  -14487 -14046.00 -13998.49 -14263.46
 62  -14291 -14156.75 -14460.17 -14266.83
 63  -15588 -14571.75 -14468.56 -14446.98
 64  -15560 -14981.50 -15584.17 -14598.51
 65  -15398 -15209.25 -15537.82 -14707.52
 66  -14772 -15329.50 -15312.30 -14715.90
 67  -13744 -14868.50 -14631.27 -14582.07
 68  -11820 -13933.50 -13480.60 -14203.88
 69  -11672 -13002.00 -11799.74 -13856.51
 70  -10179 -11853.75 -11467.61 -13352.62
 71  -10777 -11112.00 -10260.87 -12999.48
 72  -10997 -10906.25 -10807.12 -12724.93
 73  -11545 -10874.50 -11072.02 -12562.59
 74  -12531 -11462.50 -11679.98 -12557.76
 75  -12242 -11828.75 -12491.44 -12513.88
 76  -13402 -12430.00 -12400.80 -12634.70
 77  -14484 -13164.75 -13550.12 -12887.26
 78  -15775 -13975.75 -14660.74 -13282.37
 79  -15303 -14741.00 -15710.38 -13558.67
 80  -15852 -15353.50 -15378.16 -13872.05
 81  -16164 -15773.50 -15894.71 -14185.77
 82  -15527 -15711.50 -16076.79 -14368.72
 83  -15597 -15785.00 -15536.58 -14536.25
 84  -15437 -15681.25 -15575.10 -14659.35
 85  -16004 -15641.25 -15514.62 -14843.13
 86  -16180 -15804.50 -16028.09 -15026.04
 87  -15953 -15893.50 -16148.92 -15152.91
 88  -15881 -16004.50 -15943.14 -15251.80
 89  -15876 -15972.50 -15880.31 -15336.56
 90  -15904 -15903.50 -15879.83 -15413.76
 91  -15897 -15889.50 -15903.04 -15479.26
 92  -15872 -15887.25 -15893.58 -15532.80
 93  -15842 -15878.75 -15867.89 -15574.44
 94  -16092 -15925.75 -15876.22 -15644.91
 95  -15928 -15933.50 -16069.55 -15682.88
 96  -15838 -15925.00 -15915.68 -15703.36
 97  -15905 -15940.75 -15847.17 -15730.65
 98  -15810 -15870.25 -15891.99 -15740.95
 99  -15840 -15848.25 -15814.11 -15753.69
100  -15885 -15860.00 -15846.16 -15771.07
];

plot(data1(:,1),data1(:,2));
hold on
plot(data1(:,1),data1(:,3));
plot(data1(:,1),data1(:,4));
plot(data1(:,1),data1(:,5));
hold off
xlabel('Sample Number');
ylabel('Acceleration Z');
legend('aZ raw','MAF4','FIR', 'IIR');