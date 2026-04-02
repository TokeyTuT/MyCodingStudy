package www.tokeytut.ui;

import javax.swing.*;
import javax.swing.border.BevelBorder;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.Random;

public class GameJFrame extends JFrame implements KeyListener, ActionListener {
    //定义图片的数量
    private final int WIDTH_NUMBERS = 4;
    private final int HEIGHT_NUMBERS = 4;
    //定义每个图片的尺寸
    private final int IMG_WIDTH = 105;
    private final int IMG_HEIGHT = 105;
    private final int[][] WIN = new int[][]{
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12},
        {13,14,15,0}
    };
    private final int[][] data = new int[WIDTH_NUMBERS][HEIGHT_NUMBERS];

    private int cntStep;
    //空白格子的位置
    private int blank_x;
    private int blank_y;

    //创建选项下面的条目对象
    JMenuItem replayItem = new JMenuItem("重新开始");
    JMenuItem logoutItem = new JMenuItem("注销");
    JMenuItem closeItem = new JMenuItem("关闭游戏");

    JMenuItem weChatItem = new JMenuItem("微信号");


    private String path = "puzzlegame/img/animal/animal1/";

    public GameJFrame() {

        //初始化界面
        initJFrame();

        //初始化菜单栏
        initJMenuBar();

        //初始化数据
        initData();

        //初始化图片
        initImg();

        //显示界面
        this.setVisible(true);

    }

    //初始化数据
    private void initData() {
        cntStep = 0;
        Random r = new Random();
        int[] arr = new int[WIDTH_NUMBERS * HEIGHT_NUMBERS];
        for(int i = 0;i<arr.length;i++){
            arr[i] = i;
        }

        for(int i = 0;i < HEIGHT_NUMBERS;i++){
            int idx = r.nextInt(arr.length);
            //将随机索引上的数和当前索引调换位置，实现打乱算法
            int tempIdx = arr[idx];
            arr[idx] = arr[i];
            arr[i] = tempIdx;
        }

        //存入二维数组中
        for(int i = 0;i < WIDTH_NUMBERS * HEIGHT_NUMBERS;i++){
            if(arr[i] == 0){
                blank_x = i / 4;
                blank_y = i % 4;
            }
            data[i / 4][i % 4] = arr[i];
        }

    }

    //初始化图片
    private void initImg() {

        //清除图片
        this.getContentPane().removeAll();

        //显示步数
        JLabel step = new JLabel("步数：" + cntStep);
        step.setBounds(50,30,100,20);
        this.getContentPane().add(step);

        //判断是否胜利
        if(victor()){
            System.out.println("恭喜通关");
            JLabel win = new JLabel(new ImageIcon("puzzlegame/img/win.png"));
            win.setBounds(203,283,197,73);
            this.getContentPane().add(win);

        }

        //相对路径：包含盘符
        //绝对路径：从当前项目开始索引，注意是项目，不是包。

        //细节：先加载的图片覆盖在上方，后加载的图片覆盖在下方


        for(int i = 0;i < HEIGHT_NUMBERS;i++){
            for(int j = 0;j < WIDTH_NUMBERS;j++){
                JLabel label = new JLabel(new ImageIcon(path + data[i][j] +".jpg"));
                label.setBounds(j * IMG_WIDTH + 83,i * IMG_HEIGHT + 134,IMG_WIDTH,IMG_HEIGHT);

                label.setBorder(new BevelBorder(BevelBorder.RAISED));
                this.getContentPane().add(label);
            }
        }

        //添加背景图片 注意一定要写到上面加载图片的后面
        ImageIcon background = new ImageIcon("puzzlegame/img/background.png");
        JLabel jl = new JLabel(background);
        jl.setBounds(40,40,508,560);
        this.getContentPane().add(jl);

        this.getContentPane().repaint();
    }

    private boolean victor() {
        for(int i = 0;i<HEIGHT_NUMBERS;i++){
            for(int j = 0;j<WIDTH_NUMBERS;j++){
                if(data[i][j] != WIN[i][j]) return false;
            }
        }
        return true;
    }

    //初始化界面
    private void initJFrame() {
        //设置界面大小
        this.setSize(603,680);
        //设置标题
        this.setTitle("拼图游戏 v 1.0");
        //让界面置顶
        this.setAlwaysOnTop(true);
        //让界面居中
        this.setLocationRelativeTo(null);
        //关闭程序之后自动关闭虚拟机
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);//this.setDefaultCloseOperation(3);
        //取消默认的跟踪放置
        this.setLayout(null);
        //添加键盘监听事件
        this.addKeyListener(this);
    }

    //初始化菜单栏
    private void initJMenuBar() {
        //创建菜单对象
        JMenuBar jMenuBar = new JMenuBar();

        //创建选项
        JMenu fuctionJMenu = new JMenu("功能");
        JMenu aboutJMenu = new JMenu("关于我们");




        //给条目绑定事件
        replayItem.addActionListener(this);
        logoutItem.addActionListener(this);
        closeItem.addActionListener(this);
        weChatItem.addActionListener(this);

        //添加条目
        fuctionJMenu.add(replayItem);
        fuctionJMenu.add(logoutItem);
        fuctionJMenu.add(closeItem);

        aboutJMenu.add(weChatItem);

        //将选项添加到菜单中
        jMenuBar.add(fuctionJMenu);
        jMenuBar.add(aboutJMenu);


        //设置菜单
        this.setJMenuBar(jMenuBar);
    }

    private boolean swap(int x1,int y1,int x2,int y2){
        if(x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0 || y1 >= WIDTH_NUMBERS || x1 >= HEIGHT_NUMBERS || y2 >= WIDTH_NUMBERS || x2>= HEIGHT_NUMBERS){
            return false;
        }

        int img1 = data[x1][y1];
        data[x1][y1] = data[x2][y2];
        data[x2][y2] = img1;

        return true;
    }

    @Override
    public void keyTyped(KeyEvent e) {
        //略
    }

    @Override
    public void keyPressed(KeyEvent e) {
        if(victor()){
            return;
        }
        //实现一下：按住 A 不放呈现原图
        int code = e.getKeyCode();
        System.out.println(code);
        if(code == 81){
            this.getContentPane().removeAll();

            JLabel all = new JLabel(new ImageIcon(path+"all.jpg"));
            all.setBounds(40,40,508,560);
            this.getContentPane().add(all);

            //加载背景图片
            ImageIcon background = new ImageIcon("puzzlegame/img/background.png");
            JLabel jl = new JLabel(background);
            jl.setBounds(40,40,508,560);
            this.getContentPane().add(jl);

            this.getContentPane().repaint();
        }

    }

    @Override
    public void keyReleased(KeyEvent e) {
        //我们需要判断游戏是否胜利，如果胜利就不能在执行下面的判断
        if(victor()){
            return;
        }

        int code = e.getKeyCode();
        System.out.println(code);
        if(code == 87 || code == 38){
            System.out.println("上");
            if(swap(blank_x,blank_y,blank_x - 1,blank_y)){
                cntStep++;
                initImg();
                blank_x--;

            }

        }
        else if(code == 83 || code == 40){
            System.out.println("下");
            if(swap(blank_x,blank_y,blank_x + 1,blank_y)){
                cntStep++;
                initImg();
                blank_x++;
            }

        }
        else if(code == 65 || code == 37){
            System.out.println("左");
            if(swap(blank_x,blank_y,blank_x,blank_y - 1)){
                cntStep++;
                initImg();
                blank_y--;
            }

        }
        else if(code == 68 || code == 39){
            System.out.println("右");
            if(swap(blank_x,blank_y,blank_x,blank_y + 1)){
                cntStep++;
                initImg();
                blank_y++;
            }
        }

        else if(code == 81){
            initImg();
        }

        //一键通关
        else if(code == 90){
            for(int i = 0;i<HEIGHT_NUMBERS;i++){
                System.arraycopy(WIN[i], 0, data[i], 0, WIDTH_NUMBERS);
            }
            initImg();
        }
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        Object sc = e.getSource();
        if(sc == replayItem){
            initData();
            initImg();
        }
        else if(sc == logoutItem){
            this.setVisible(false);
            new LoginJFrame();
        }
        else if(sc == closeItem){
            System.exit(0);
        }
        else if(sc == weChatItem){
            JDialog jd = new JDialog();
            JLabel wechat = new JLabel(new ImageIcon("puzzlegame/img/wechat.jpg"));
            wechat.setBounds(50, 30, 194, 194);
            jd.getContentPane().add(wechat);
            jd.setSize(270, 270);
            jd.setAlwaysOnTop(true);
            jd.setLocationRelativeTo(null);
            jd.setModal(true);
            jd.setVisible(true);
        }
    }
}
