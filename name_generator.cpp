#include <iostream>
#include <fstream>
#include <string>
#include <random>
using namespace std;

template <size_t N, typename T>
constexpr size_t how_many(T (&a)[N]){return N;}

string surnameword[] = {u8"陳", u8"林", u8"黃", u8"張", u8"李", u8"王", u8"吳", u8"劉", u8"蔡", u8"楊", u8"許", u8"鄭", u8"謝", u8"洪", u8"郭", u8"邱", u8"曾", u8"廖", u8"賴", u8"徐", u8"周", u8"葉", u8"蘇", u8"莊", u8"呂", u8"江", u8"何", u8"蕭", u8"羅", u8"高", u8"潘", u8"簡", u8"朱", u8"鍾", u8"彭", u8"游", u8"詹", u8"胡", u8"施", u8"沈", u8"余", u8"盧", u8"梁", u8"趙", u8"顏", u8"柯", u8"翁", u8"魏", u8"孫", u8"戴", u8"范", u8"方", u8"宋", u8"鄧", u8"杜", u8"傅", u8"侯", u8"曹", u8"薛", u8"丁", u8"卓", u8"馬", u8"阮", u8"董", u8"唐", u8"溫", u8"藍", u8"蔣", u8"石", u8"古", u8"紀", u8"姚", u8"連", u8"馮", u8"歐", u8"程", u8"湯", u8"黄", u8"田", u8"康", u8"姜", u8"汪", u8"白", u8"鄒", u8"尤", u8"巫", u8"鐘", u8"黎", u8"涂", u8"龔", u8"嚴", u8"韓", u8"袁", u8"金", u8"童", u8"陸", u8"夏", u8"柳", u8"凃", u8"邵"};
constexpr int surnamehot[] = {1000, 990, 980, 970, 960, 950, 940, 930, 920, 910, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11};
string nameword[] = {u8"怡", u8"文", u8"婷", u8"雅", u8"佳", u8"君", u8"志", u8"嘉", u8"俊", u8"家", u8"宏", u8"偉", u8"明", u8"慧", u8"欣", u8"宜", u8"惠", u8"彥", u8"如", u8"瑋", u8"宇", u8"豪", u8"芳", u8"建", u8"雯", u8"佩", u8"育", u8"柏", u8"凱", u8"智", u8"哲", u8"宗", u8"維", u8"銘", u8"傑", u8"淑", u8"玲", u8"冠", u8"穎", u8"玉", u8"翔", u8"瑜", u8"華", u8"廷", u8"孟", u8"政", u8"儀", u8"安", u8"仁", u8"郁", u8"涵", u8"子", u8"靜", u8"翰", u8"美", u8"國", u8"庭", u8"思", u8"軒", u8"珊", u8"賢", u8"珮", u8"瑩", u8"霖", u8"儒", u8"蓉", u8"正", u8"瑞", u8"鈞", u8"秀", u8"鴻", u8"倫", u8"伶", u8"盈", u8"琪", u8"萱", u8"威", u8"元", u8"佑", u8"信", u8"德", u8"立", u8"聖", u8"詩", u8"世", u8"婉", u8"潔", u8"昱", u8"鈺", u8"樺", u8"敏", u8"姿", u8"榮", u8"承", u8"慈", u8"曉", u8"奕", u8"芬", u8"書", u8"逸", u8"萍", u8"馨", u8"士", u8"真", u8"毅", u8"祥", u8"茹", u8"中", u8"筱", u8"琳", u8"菁", u8"弘", u8"良", u8"博", u8"娟", u8"慶", u8"芸", u8"勳", u8"依", u8"達", u8"心", u8"永", u8"恩", u8"韋", u8"成", u8"峰", u8"毓", u8"杰", u8"緯", u8"宛", u8"昌", u8"振", u8"璇", u8"麗", u8"于", u8"妤", u8"忠", u8"青", u8"誠", u8"裕", u8"龍", u8"均", u8"民", u8"淳", u8"貞", u8"旻", u8"容", u8"純", u8"平", u8"皓", u8"品", u8"耀", u8"昇", u8"寧", u8"勝", u8"憲", u8"浩", u8"靖", u8"啟", u8"吟", u8"英", u8"莉", u8"辰", u8"韻", u8"薇", u8"健", u8"綺", u8"蕙", u8"瑄", u8"仲", u8"秋", u8"秉", u8"群", u8"祐", u8"修", u8"亭", u8"珍", u8"揚", u8"昭", u8"琦", u8"任", u8"益", u8"源", u8"光", u8"詠", u8"玟", u8"景", u8"富", u8"駿", u8"柔", u8"泰", u8"閔", u8"羽", u8"輝", u8"堯", u8"雲", u8"琬", u8"峻", u8"蓁", u8"伊", u8"禎", u8"燕", u8"千", u8"易", u8"東", u8"巧", u8"鳳", u8"昀", u8"致", u8"培", u8"晴", u8"漢", u8"伯", u8"睿", u8"芝", u8"敬", u8"義", u8"亞", u8"方", u8"興", u8"翊", u8"清", u8"鈴", u8"筠", u8"玫", u8"一", u8"瓊", u8"隆", u8"丞", u8"倩", u8"麟", u8"晏", u8"岳", u8"湘", u8"崇", u8"帆", u8"臻", u8"強", u8"欽", u8"展", u8"沛", u8"雄", u8"尚", u8"雨", u8"晉", u8"名", u8"竹", u8"甫", u8"旭", u8"喬", u8"澤", u8"諭", u8"宣", u8"俐", u8"斌", u8"凡", u8"紹", u8"泓", u8"學", u8"筑", u8"甄", u8"舒", u8"坤", u8"謙", u8"梅", u8"若", u8"璋", u8"舜", u8"全", u8"琇", u8"遠", u8"奇", u8"俞", u8"芷", u8"映", u8"盛", u8"金", u8"虹", u8"懿", u8"蘭", u8"婕", u8"新", u8"碩", u8"乃", u8"彬", u8"仕", u8"媛", u8"融", u8"孝", u8"豐", u8"錦", u8"意", u8"嵐", u8"諺", u8"至", u8"彰", u8"淵", u8"天", u8"吉", u8"尹", u8"昕", u8"大", u8"云", u8"祺", u8"汝", u8"順", u8"瑾", u8"瀚", u8"松", u8"榕", u8"姵", u8"力", u8"又", u8"幸", u8"和", u8"齡", u8"昆", u8"男", u8"人", u8"憶", u8"之", u8"勇", u8"捷", u8"陽", u8"晨", u8"原", u8"以", u8"齊", u8"超", u8"為", u8"誼", u8"采", u8"雪", u8"朝", u8"鑫", u8"恆", u8"鵬", u8"菱", u8"兆", u8"長", u8"卉", u8"惟", u8"邦", u8"卿", u8"生", u8"楷", u8"竣", u8"香", u8"亮", u8"亦", u8"誌", u8"妍", u8"春", u8"程", u8"銓", u8"煒", u8"綸", u8"暐", u8"愷", u8"素", u8"其", u8"小", u8"瑛", u8"紋", u8"姍", u8"妮", u8"碧", u8"季", u8"福", u8"汶", u8"治", u8"鋒", u8"妙", u8"暉", u8"綾", u8"桂", u8"鼎", u8"勛", u8"晟", u8"叡", u8"禹", u8"星", u8"可", u8"聰", u8"寬", u8"煜", u8"洋", u8"億", u8"翎", u8"騰", u8"淇", u8"月", u8"鎮", u8"呈", u8"宥", u8"貴", u8"桓", u8"棋", u8"利", u8"茵", u8"茜", u8"凌", u8"懷", u8"羿", u8"寶", u8"妏", u8"岑", u8"岱", u8"麒", u8"瑤", u8"進", u8"璟", u8"屏", u8"嫻", u8"琮", u8"蘋", u8"友", u8"章", u8"侑", u8"念", u8"康", u8"蔚", u8"曜", u8"蓮", u8"亨", u8"林", u8"延", u8"森", u8"恬", u8"權", u8"上", u8"宸", u8"蓓", u8"琴", u8"函", u8"剛", u8"煌", u8"耿", u8"茂", u8"彤", u8"玄", u8"允", u8"瀅", u8"升", u8"勤", u8"劭", u8"少", u8"珈", u8"音", u8"介", u8"馥", u8"克", u8"南", u8"繼", u8"霆", u8"年", u8"傳", u8"錡", u8"昶", u8"苓", u8"曼", u8"葳", u8"渝", u8"蒨", u8"翠", u8"顯", u8"禮", u8"瑀", u8"百", u8"典", u8"善", u8"紀", u8"榆", u8"肇", u8"羚", u8"迪", u8"炳", u8"霈", u8"煥", u8"州", u8"有", u8"得", u8"賓", u8"皇", u8"道", u8"洲", u8"綱", u8"祖", u8"棠", u8"雁", u8"先", u8"紫", u8"霞", u8"重", u8"斐", u8"璿", u8"喻", u8"佐", u8"航", u8"錚", u8"珠", u8"芃", u8"杏", u8"川", u8"梓", u8"恒", u8"武", u8"苑", u8"藝", u8"孜", u8"評", u8"定", u8"然", u8"曄", u8"耕", u8"陵", u8"勻", u8"言", u8"菀", u8"嫺", u8"震", u8"聿", u8"鳴", u8"艾", u8"登", u8"希", u8"儷", u8"韶", u8"予", u8"炫", u8"頤", u8"薏", u8"基", u8"紘", u8"守", u8"葦", u8"堂", u8"棻", u8"歆", u8"能", u8"妃", u8"谷", u8"訓", u8"崴", u8"彩", u8"資", u8"陞", u8"珺", u8"山", u8"衡", u8"軍", u8"仰", u8"乙", u8"聲", u8"嬿", u8"加", u8"斯", u8"城", u8"熙", u8"海", u8"愛", u8"螢", u8"薰", u8"衍", u8"村", u8"科", u8"媚", u8"苡", u8"驊", u8"浚", u8"胤", u8"夫", u8"唯", u8"微", u8"芊", u8"芯", u8"伸", u8"廣", u8"則", u8"丹", u8"祈", u8"厚", u8"卓", u8"鐘", u8"奎", u8"發", u8"淨", u8"悅", u8"玠", u8"勁", u8"楓", u8"譽", u8"輔", u8"燁", u8"尉", u8"甯", u8"保", u8"津", u8"錫", u8"璽", u8"語", u8"鎧", u8"騏", u8"雍", u8"郡", u8"沂", u8"暄", u8"夢", u8"含", u8"倍", u8"硯", u8"時", u8"照", u8"業", u8"穗", u8"霓", u8"運", u8"澄", u8"懋", u8"寰", u8"幼", u8"堅", u8"櫻", u8"棟", u8"昊", u8"忻", u8"合", u8"縈", u8"楨", u8"京", u8"樹", u8"濬", u8"獻", u8"禾", u8"璧", u8"晶", u8"貝", u8"慕", u8"盟", u8"耘", u8"仙", u8"璁", u8"江", u8"行", u8"靈", u8"敦", u8"絜", u8"逢", u8"日", u8"牧", u8"嬋", u8"存", u8"本", u8"理", u8"徽", u8"顥", u8"令", u8"雋", u8"愉", u8"楚", u8"農", u8"閎", u8"相", u8"高", u8"同", u8"苹", u8"律", u8"茗", u8"沅", u8"譯", u8"經", u8"右", u8"旺", u8"才", u8"暘", u8"崧", u8"蒼", u8"衛", u8"晃", u8"恭", u8"魁", u8"姝", u8"議", u8"自", u8"泉", u8"玥", u8"汎", u8"樵", u8"賀", u8"凰", u8"貽", u8"泳", u8"謹", u8"葶", u8"萬", u8"殷", u8"炯", u8"蕾", u8"頡", u8"復", u8"娜", u8"涓", u8"財", u8"荃", u8"娥", u8"余", u8"澔", u8"助", u8"芹", u8"芮", u8"格", u8"倢", u8"沁", u8"頻", u8"乾", u8"田", u8"唐", u8"眉", u8"釗", u8"樂", u8"崑", u8"倚", u8"淯", u8"增", u8"珣", u8"飛", u8"琨", u8"今", u8"御", u8"芩", u8"稚", u8"弦", u8"鍾", u8"邑", u8"鍵", u8"頌", u8"師", u8"朋", u8"挺", u8"添", u8"潤", u8"璘", u8"慎", u8"端", u8"偲", u8"烜", u8"丁", u8"開", u8"秦", u8"昂", u8"濟", u8"霙", u8"曦", u8"惇", u8"向", u8"圻", u8"炘", u8"楠", u8"旗", u8"笙", u8"豫", u8"鶴", u8"滿", u8"知", u8"洵", u8"枝", u8"珩", u8"徵", u8"鉦", u8"儂", u8"三", u8"協", u8"丰", u8"濱", u8"常", u8"嫚", u8"嵩", u8"絹", u8"植", u8"期", u8"台", u8"翌", u8"貿", u8"岡", u8"銀", u8"洪", u8"連", u8"奐", u8"滋", u8"霜", u8"藍", u8"戎", u8"妘", u8"廉", u8"鑬", u8"蔓", u8"熹", u8"庚", u8"夙", u8"佾", u8"爾", u8"靚", u8"尊", u8"燦", u8"享", u8"詔", u8"申", u8"根", u8"臣", u8"嬅", u8"泊", u8"親", u8"詮", u8"圓", u8"菡", u8"壬", u8"樑", u8"弼", u8"爵", u8"應", u8"溢", u8"倉", u8"鐴", u8"琛", u8"錞", u8"璞", u8"熒", u8"筌", u8"嫣", u8"莞", u8"侃", u8"歡", u8"黛", u8"巍", u8"瑱", u8"璉", u8"嶸", u8"喜", u8"祿", u8"僑", u8"木", u8"穆", u8"彧", u8"菊", u8"居", u8"灝", u8"竺", u8"琁", u8"磊", u8"雙", u8"紅", u8"倪", u8"証", u8"媜", u8"杉", u8"諄", u8"睦", u8"萩", u8"見", u8"詒", u8"聆", u8"適", u8"淩", u8"怜", u8"壹", u8"濠", u8"臨", u8"印", u8"河", u8"紜", u8"賜", u8"樟", u8"咨", u8"禕", u8"偵", u8"鎂", u8"彗", u8"濤", u8"嚴", u8"因", u8"淞", u8"主", u8"勵", u8"竑", u8"芙", u8"姮", u8"旋", u8"沐", u8"燿", u8"玨", u8"緒", u8"嫈", u8"創", u8"焜", u8"環", u8"郎", u8"帝", u8"絢", u8"太", u8"媺", u8"叔", u8"霏", u8"白", u8"屹", u8"榛", u8"菘", u8"必", u8"久", u8"潁", u8"謀", u8"吾", u8"舟", u8"箴", u8"璨", u8"匡", u8"瑢", u8"綿", u8"蒂", u8"貫", u8"玹", u8"陳", u8"鉅", u8"蘊", u8"翼", u8"代", u8"憓", u8"琄", u8"詳", u8"艷", u8"荷", u8"倖", u8"功", u8"風", u8"禧", u8"池", u8"韓", u8"荏", u8"澐", u8"顗", u8"棨", u8"炎", u8"贊", u8"湧", u8"漪", u8"湄", u8"頎", u8"溱", u8"境", u8"琍", u8"溥", u8"瀛", u8"璐", u8"鏡", u8"兒", u8"壕", u8"珀", u8"縉", u8"幃", u8"鎔", u8"柄", u8"聯", u8"迺", u8"淙", u8"法", u8"賦", u8"嬌", u8"寅", u8"在", u8"詣", u8"猷", u8"範", u8"楹", u8"垣", u8"宴", u8"攸", u8"競", u8"羲", u8"緣", u8"量", u8"里", u8"舫", u8"躍", u8"恕", u8"渟", u8"滄", u8"稜", u8"淮", u8"鋐", u8"足", u8"桐", u8"芫", u8"周", u8"洛", u8"壽", u8"豊", u8"韡", u8"鎰", u8"曲", u8"琤", u8"帥", u8"瓏", u8"侖", u8"分", u8"策", u8"嬪", u8"橋", u8"玶", u8"韜", u8"紳", u8"園", u8"鉉", u8"聞", u8"菖", u8"夏", u8"瑗", u8"玳", u8"薪", u8"越", u8"梵", u8"絲", u8"巽", u8"鑑", u8"晁", u8"濃", u8"泱", u8"裴", u8"勃", u8"雰", u8"娸", u8"垂", u8"寒", u8"銜", u8"煦", u8"朱", u8"璦", u8"烈", u8"莊", u8"米", u8"熏", u8"堉", u8"觀", u8"堡", u8"繁", u8"官", u8"謦", u8"前", u8"榜", u8"溶", u8"澍", u8"襄", u8"珽", u8"鐸", u8"祝", u8"玓", u8"序", u8"水", u8"逵", u8"駒", u8"琡", u8"冬", u8"洳", u8"通", u8"司", u8"洺", u8"溫", u8"醇", u8"來", u8"巖", u8"烽", u8"蕎", u8"邵", u8"禪", u8"緻", u8"鵑", u8"岐", u8"塵", u8"而", u8"式", u8"棣", u8"錩", u8"玗", u8"餘", u8"嶽", u8"輯", u8"洧", u8"后", u8"記", u8"夆", u8"釧", u8"仟", u8"驛", u8"繹", u8"莘", u8"浤", u8"起", u8"虔", u8"帛", u8"述", u8"衣", u8"峙", u8"佶", u8"黃", u8"崙", u8"祁", u8"宓", u8"憬", u8"枚", u8"擎", u8"咸", u8"笛", u8"淋", u8"鍇", u8"材", u8"栩", u8"娉", u8"蒲", u8"壯", u8"迎", u8"劍", u8"諠", u8"圳", u8"皖", u8"拓", u8"銳", u8"絮", u8"匯", u8"蕓", u8"楊", u8"坪", u8"臺", u8"驥", u8"嗣", u8"煇", u8"慰", u8"作", u8"效", u8"再", u8"專", u8"丕", u8"妗", u8"諾", u8"李", u8"澧", u8"悌", u8"奉", u8"泯", u8"棉", u8"釋", u8"萌", u8"笠", u8"執", u8"庸", u8"臆", u8"葆", u8"鋼", u8"界", u8"葉", u8"姜", u8"崢", u8"證", u8"綠", u8"桑", u8"蟬", u8"初", u8"黎", u8"孫", u8"於", u8"鄉", u8"首", u8"杭", u8"茲", u8"擇", u8"錕", u8"宙", u8"陸", u8"從", u8"普", u8"築", u8"椿", u8"蒔", u8"祉", u8"炤", u8"膺", u8"樞", u8"張", u8"冰", u8"嫆", u8"委", u8"葵", u8"紓", u8"倬", u8"燊", u8"招", u8"肯", u8"菲", u8"勉", u8"阡", u8"徹", u8"朗", u8"蜜", u8"多", u8"顏", u8"樸", u8"辛", u8"研", u8"波", u8"湞", u8"與", u8"蕊", u8"女", u8"緹", u8"卜", u8"祚", u8"直", u8"赫", u8"竟", u8"諴", u8"揮", u8"澂", u8"晞", u8"模", u8"彙", u8"柳", u8"泠", u8"甲", u8"濰", u8"癸", u8"柱", u8"洸", u8"纓", u8"槿", u8"坊", u8"圭", u8"綜", u8"繡", u8"瓔", u8"絨", u8"統", u8"化", u8"旂", u8"瑟", u8"雀", u8"席", u8"石", u8"霽", u8"淼", u8"施", u8"約", u8"淦", u8"孔", u8"姬", u8"茱", u8"珂", u8"岫", u8"嶔", u8"讚", u8"教", u8"苾", u8"秩", u8"鐙", u8"弈", u8"崎", u8"畯", u8"積", u8"岷", u8"苗", u8"喨", u8"伍", u8"璠", u8"珞", u8"迦", u8"荻", u8"冀", u8"嬬", u8"侯", u8"公", u8"尤", u8"漳", u8"位", u8"礽", u8"府", u8"舉", u8"媄", u8"薈", u8"暖", u8"娣", u8"礎", u8"圃", u8"隚", u8"衿", u8"瀠", u8"諳", u8"鏞", u8"詞", u8"穩", u8"曙", u8"菽", u8"絃", u8"砡", u8"鶯", u8"禛", u8"剴", u8"望", u8"懌", u8"朕", u8"婧", u8"狄", u8"桀", u8"諒", u8"節", u8"劼", u8"俋", u8"引", u8"王", u8"九", u8"營", u8"莛", u8"薔", u8"己", u8"騫", u8"非", u8"輿", u8"苔", u8"員", u8"岩", u8"湛", u8"潭", u8"瀧", u8"嶢", u8"顓", u8"履", u8"囿", u8"昉", u8"識", u8"窈", u8"恂", u8"裔", u8"嶺", u8"濡", u8"揆", u8"丘", u8"脩", u8"卲", u8"宮", u8"瑭", u8"蝶", u8"筆", u8"諦", u8"將", u8"深", u8"旼", u8"彝", u8"贏", u8"巨", u8"孚", u8"晢", u8"北", u8"殿", u8"忞", u8"棓", u8"露", u8"敘", u8"巾", u8"樓", u8"涴", u8"旬", u8"凝", u8"圜", u8"愈", u8"梨", u8"旅", u8"呂", u8"特", u8"省", u8"果", u8"璜", u8"由", u8"竫", u8"旆", u8"造", u8"磬", u8"畇", u8"熠", u8"萃", u8"閣", u8"集", u8"讌", u8"嶧", u8"梧", u8"蔆", u8"覺", u8"虎", u8"地", u8"稟", u8"潓", u8"實", u8"讓", u8"陶", u8"港", u8"槐", u8"圖", u8"鋆", u8"皎", u8"訢", u8"精", u8"遙", u8"玎", u8"价", u8"優", u8"寓", u8"郅", u8"皆", u8"鎬", u8"浥", u8"罡", u8"嬛", u8"吏", u8"瓅", u8"情", u8"緗", u8"歷", u8"花", u8"吳", u8"好", u8"燈", u8"橙", u8"旖", u8"兼", u8"佰", u8"際", u8"字", u8"豔", u8"及", u8"會", u8"渼", u8"恪", u8"雷", u8"鄭", u8"陙", u8"論", u8"頂", u8"妡", u8"都", u8"乘", u8"鍠", u8"鋕", u8"許", u8"弋", u8"曾", u8"釆", u8"皜", u8"潮", u8"阜", u8"庠", u8"浦", u8"楙", u8"煖", u8"垚", u8"莆", u8"勢", u8"後", u8"蔭", u8"熾", u8"媗", u8"溪", u8"綵", u8"似", u8"圍", u8"軫", u8"劉", u8"也", u8"鈜", u8"蔡", u8"菩", u8"二", u8"峪", u8"勗", u8"鉞", u8"沿", u8"養", u8"何", u8"簡", u8"汪", u8"翡", u8"用", u8"舲", u8"央", u8"湖", u8"焄", u8"巡", u8"豈", u8"選", u8"藹", u8"錄", u8"鏵", u8"愔", u8"繪", u8"邁", u8"梁", u8"旨"};
constexpr int namehot[] = {13925, 13858, 12641, 11848, 10657, 10382, 9313, 8127, 8044, 7971, 7876, 7621, 7597, 7575, 7304, 7194, 7130, 7081, 6933, 6776, 6566, 6548, 6472, 6315, 6178, 6071, 6009, 5832, 5824, 5709, 5488, 5431, 5316, 5164, 5030, 5011, 4999, 4892, 4774, 4766, 4710, 4648, 4569, 4559, 4505, 4468, 4464, 4327, 4320, 4248, 4214, 4167, 4034, 4024, 3950, 3903, 3857, 3806, 3619, 3607, 3584, 3568, 3522, 3518, 3510, 3420, 3398, 3371, 3346, 3330, 3321, 3298, 3226, 3221, 3197, 3186, 3136, 3133, 3125, 3065, 3056, 3031, 3020, 3000, 2999, 2947, 2901, 2855, 2850, 2843, 2832, 2760, 2752, 2750, 2712, 2712, 2705, 2696, 2667, 2659, 2612, 2586, 2565, 2515, 2500, 2448, 2448, 2447, 2424, 2384, 2345, 2332, 2324, 2319, 2303, 2295, 2288, 2235, 2203, 2189, 2184, 2166, 2160, 2127, 2127, 2039, 2026, 2018, 2003, 1984, 1980, 1957, 1956, 1950, 1940, 1933, 1921, 1902, 1896, 1878, 1868, 1854, 1822, 1816, 1815, 1810, 1806, 1778, 1773, 1767, 1762, 1752, 1716, 1686, 1678, 1675, 1653, 1651, 1647, 1636, 1633, 1632, 1616, 1616, 1615, 1614, 1610, 1605, 1593, 1588, 1588, 1554, 1552, 1549, 1536, 1535, 1516, 1510, 1506, 1500, 1487, 1472, 1454, 1390, 1388, 1388, 1386, 1386, 1383, 1379, 1367, 1365, 1351, 1332, 1296, 1290, 1289, 1286, 1283, 1275, 1274, 1259, 1258, 1253, 1251, 1250, 1248, 1245, 1236, 1234, 1220, 1218, 1217, 1213, 1213, 1210, 1202, 1186, 1184, 1183, 1170, 1169, 1163, 1163, 1156, 1155, 1144, 1143, 1141, 1139, 1137, 1133, 1126, 1125, 1122, 1120, 1115, 1089, 1082, 1082, 1079, 1054, 1054, 1052, 1050, 1046, 1045, 1039, 1037, 1034, 1032, 1023, 1019, 1016, 1013, 1004, 1003, 1001, 992, 987, 984, 983, 977, 976, 964, 963, 955, 952, 950, 941, 939, 938, 933, 924, 920, 918, 918, 917, 903, 903, 896, 896, 889, 886, 886, 882, 872, 871, 871, 858, 857, 855, 851, 849, 841, 840, 838, 836, 824, 819, 818, 816, 815, 814, 806, 805, 802, 801, 800, 798, 797, 795, 794, 776, 775, 770, 770, 767, 765, 759, 758, 752, 740, 729, 720, 711, 708, 706, 706, 704, 699, 699, 695, 689, 689, 687, 687, 686, 683, 683, 679, 668, 667, 667, 664, 663, 661, 659, 659, 656, 647, 647, 646, 646, 644, 643, 641, 636, 631, 630, 629, 627, 626, 625, 624, 623, 621, 619, 617, 614, 613, 610, 609, 609, 607, 606, 597, 597, 597, 595, 587, 585, 584, 582, 576, 574, 570, 566, 564, 561, 560, 560, 557, 554, 544, 539, 537, 529, 528, 528, 528, 527, 525, 519, 519, 519, 519, 515, 514, 507, 506, 504, 504, 503, 501, 500, 499, 499, 497, 488, 484, 483, 482, 482, 478, 477, 476, 475, 473, 468, 467, 456, 452, 449, 447, 438, 438, 435, 435, 432, 426, 424, 424, 422, 418, 414, 413, 411, 409, 408, 407, 404, 404, 403, 400, 398, 390, 389, 389, 388, 388, 387, 387, 385, 384, 384, 383, 382, 382, 381, 381, 380, 378, 378, 378, 374, 371, 371, 371, 369, 367, 365, 363, 363, 359, 359, 358, 355, 355, 350, 348, 347, 345, 344, 340, 338, 338, 337, 337, 336, 336, 334, 332, 330, 329, 325, 321, 318, 316, 314, 314, 314, 312, 311, 311, 310, 309, 309, 306, 305, 304, 304, 304, 303, 302, 301, 301, 300, 300, 299, 298, 297, 294, 294, 294, 293, 292, 289, 289, 288, 287, 287, 285, 285, 285, 285, 284, 281, 279, 277, 273, 272, 272, 271, 270, 270, 270, 267, 266, 265, 262, 262, 261, 260, 260, 260, 259, 259, 259, 258, 258, 257, 257, 256, 255, 254, 252, 250, 247, 245, 244, 244, 243, 242, 242, 242, 242, 241, 241, 240, 238, 238, 237, 236, 236, 235, 235, 234, 234, 233, 233, 231, 231, 230, 230, 230, 229, 228, 228, 228, 227, 227, 226, 226, 225, 225, 223, 221, 220, 220, 220, 220, 219, 215, 213, 213, 213, 213, 212, 212, 211, 210, 209, 209, 209, 205, 205, 205, 204, 203, 203, 200, 199, 198, 198, 197, 195, 195, 194, 194, 193, 193, 192, 189, 188, 188, 186, 185, 185, 185, 184, 184, 183, 183, 183, 181, 181, 179, 179, 178, 178, 177, 177, 176, 176, 175, 175, 173, 172, 171, 171, 171, 171, 170, 169, 169, 169, 168, 167, 166, 166, 165, 165, 165, 164, 162, 161, 160, 157, 153, 153, 152, 152, 152, 152, 152, 151, 149, 149, 148, 148, 146, 146, 146, 145, 145, 144, 143, 141, 141, 141, 141, 139, 139, 139, 139, 138, 138, 137, 136, 135, 135, 134, 134, 133, 131, 131, 131, 130, 130, 130, 130, 130, 129, 129, 128, 127, 127, 127, 126, 126, 126, 125, 124, 124, 124, 124, 123, 123, 123, 123, 122, 122, 121, 120, 120, 120, 119, 119, 119, 119, 118, 118, 117, 117, 116, 116, 116, 116, 115, 114, 114, 113, 113, 113, 113, 112, 112, 111, 110, 110, 110, 109, 109, 109, 109, 109, 109, 108, 108, 108, 108, 107, 107, 107, 107, 106, 106, 106, 105, 105, 105, 105, 104, 104, 103, 103, 103, 102, 102, 102, 102, 101, 101, 101, 100, 99, 99, 99, 99, 99, 99, 98, 98, 97, 96, 96, 96, 96, 94, 94, 94, 93, 93, 93, 93, 93, 93, 93, 92, 92, 91, 91, 91, 90, 90, 90, 90, 88, 88, 88, 88, 88, 88, 88, 88, 88, 87, 87, 87, 87, 87, 86, 86, 86, 86, 86, 85, 85, 85, 85, 84, 83, 83, 83, 83, 83, 82, 82, 82, 82, 82, 81, 81, 81, 81, 80, 80, 80, 79, 79, 79, 78, 78, 78, 78, 78, 78, 78, 78, 78, 77, 77, 77, 76, 76, 76, 76, 76, 76, 76, 75, 75, 75, 74, 74, 74, 74, 73, 73, 73, 73, 73, 73, 73, 73, 73, 72, 72, 71, 71, 71, 71, 71, 70, 70, 70, 70, 70, 70, 70, 70, 69, 69, 68, 68, 68, 68, 68, 68, 67, 67, 67, 66, 66, 66, 66, 66, 66, 66, 66, 65, 65, 65, 65, 65, 65, 65, 65, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 63, 63, 63, 63, 63, 63, 62, 62, 62, 62, 62, 62, 62, 62, 62, 62, 61, 61, 61, 61, 61, 61, 60, 60, 60, 60, 60, 60, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 59, 58, 58, 58, 58, 58, 58, 58, 57, 57, 57, 57, 57, 57, 57, 57, 57, 57, 56, 56, 56, 56, 56, 55, 55, 55, 55, 55, 55, 55, 55, 55, 54, 54, 54, 54, 53, 53, 53, 52, 52, 52, 52, 52, 52, 52, 51, 51, 51, 51, 51, 50, 50, 50, 50, 50, 50, 49, 49, 49, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 47, 46, 46, 46, 46, 46, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 44, 44, 44, 44, 44, 44, 44, 44, 44, 44, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 43, 42, 42, 42, 42, 42, 42, 42, 42, 42, 41, 41, 41, 41, 41, 40, 40, 40, 40, 40, 40, 40, 40, 40, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 38, 38, 38, 38, 38, 38, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 33, 33, 33, 33, 33, 33, 33, 33, 33, 33, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19};
constexpr size_t surnamenumber = how_many(surnamehot); //100
constexpr size_t namenumber = how_many(namehot); //1500

constexpr int doublename[] = {1000, 1}; //double - single
constexpr int is_samesurname[] = {1, 1}; //same - diff
constexpr int no_relative[] = {3, 1}; //no - have

constexpr int want_number = 100;

constexpr size_t seed = 65536;
mt19937_64 rd(seed);

class accumulate_generator{
public:
	template<typename Generator, size_t N>
	int operator()(Generator& g, const int (&array)[N]){
		int upper = N * array[0];
		uniform_int_distribution<> ge(0, upper - 1);
		while(true){
			int sol = ge(g);
			for(int i = 0, sum = 0;i < N;i++){
				sum += array[i];
				if(sol < sum){
					return i;
				}
			}
		}
	}
};

accumulate_generator ag;

class name_generator{
private:
	accumulate_generator ag;
public:
	name_generator(){}
	template<typename Generator>
	string just_name(Generator& g){
		string sol;
		int name_letter = (ag(g, doublename) == 0) ? 2 : 1;
		for(int i = 0;i < name_letter;i++){
			sol += nameword[ag(g, namehot)];
		}
		return sol;
	}
	template<typename Generator>
	string operator()(Generator& g){
		string sol;
		sol += surnameword[ag(g, surnamehot)];
		sol += just_name(g);
		return sol;
	}
};

name_generator ng;

class relativename_generator{
private:
	accumulate_generator ag;
	name_generator ng;
public:
	relativename_generator(){}
	template<typename Generator>
	string operator()(Generator& g, string name){
		bool diff_sur = ag(g, is_samesurname);
		if(diff_sur){
			return ng(g);
		}
		unsigned char initcode = name[0];
		int get_char = 0;
		if(initcode <= 0x7f){get_char = 1;}
		else if(initcode <= 0xdf){get_char = 2;}
		else if(initcode <= 0xef){get_char = 3;}
		else if(initcode <= 0xf7){get_char = 4;}
		//else{invalid}
		string sol;
		for(int i = 0;i < get_char;i++){
			sol += name[i];
		}
		sol += ng.just_name(g);
		return sol;
	}
};

relativename_generator rng;

int main(){
	//cout << surnamenumber;
	ofstream fout("tmp.txt");
	for(int i = 0;i < want_number;i++){
		string name = ng(rd);
		fout << name;
		while(ag(rd, no_relative) == 1){
			fout << ' ' << rng(rd, name);
		}
		fout << endl;
	}
	fout.close();
	return 0;
}
