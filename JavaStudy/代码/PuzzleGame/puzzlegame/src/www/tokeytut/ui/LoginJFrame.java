package www.tokeytut.ui;

import www.tokeytut.user.UserData;

import javax.swing.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.Random;

public class LoginJFrame extends JFrame implements MouseListener {

    private String RightCode;
    //图片
    private final JLabel usernamePhoto = new JLabel(new ImageIcon("puzzlegame/img/login/用户名.png"));
    private final JLabel pwdPhoto = new JLabel(new ImageIcon("puzzlegame/img/login/密码.png"));
    private final JLabel RightCodePhoto = new JLabel(new ImageIcon("puzzlegame/img/login/验证码.png"));
    private final JLabel background = new JLabel(new ImageIcon("puzzlegame/img/login/background.png"));

    //文本框
    private final JTextField usernameText = new JTextField();
    private final JPasswordField pwdText = new JPasswordField();
    private final JTextField rightCodeText = new JTextField();

    //按钮
    private final JButton login = new JButton(new ImageIcon("puzzlegame/img/login/登录按钮.png"));
    private final JButton register = new JButton(new ImageIcon("puzzlegame/img/login/注册按钮.png"));
    private final JButton rightCodeButton = new JButton();

    //显示密码
    private final JButton pwdVisible = new JButton(new ImageIcon("puzzlegame/img/login/显示密码.png"));
    private boolean pwdVisible_flag = false;



    public LoginJFrame() {
        //初始化界面
        initFrame();

        //初始化图片
        initView();

        //界面显示
        this.setVisible(true);
    }

    private void initView() {
        this.getContentPane().removeAll();
        //用户名
        usernamePhoto.setBounds(89,133,79,17);
        this.getContentPane().add(usernamePhoto);

        //密码
        pwdPhoto.setBounds(89,196,79,17);
        this.getContentPane().add(pwdPhoto);

        //验证码
        RightCodePhoto.setBounds(89,253,56,21);
        this.getContentPane().add(RightCodePhoto);

        //验证码文字
        rightCodeButton.setBounds(270,253,56,21);
        getNewCode();
        //给验证码绑定事件，点击验证码可以更换验证码
        rightCodeButton.addMouseListener(this);
        this.getContentPane().add(rightCodeButton);
        //用户名文本框
        usernameText.setBounds(160,133,200,25);
        this.getContentPane().add(usernameText);

        //密码文本框
        pwdText.setBounds(160,196,230,25);
        pwdText.setEchoChar('*');
        this.getContentPane().add(pwdText);
        //验证码文本框
        rightCodeText.setBounds(160,253,100,25);
        this.getContentPane().add(rightCodeText);


        //登录按钮
        login.setBounds(105,300,128,47);
        //去除边框
        login.setBorderPainted(false);
        //去除背景
        login.setContentAreaFilled(false);
        //绑定监听事件
        login.addMouseListener(this);
        this.getContentPane().add(login);

        //注册按钮
        register.setBounds(260,300,128,47);
        //去除边框
        register.setBorderPainted(false);
        //去除背景
        register.setContentAreaFilled(false);
        register.addMouseListener(this);
        this.getContentPane().add(register);

        //显示密码按钮
        pwdVisible.setBounds(386,196,18,25);
        pwdVisible.setContentAreaFilled(false);
        pwdVisible.setBorderPainted(false);
        pwdVisible.addMouseListener(this);
        this.getContentPane().add(pwdVisible);

        //添加背景
        background.setBounds(0,0, background.getWidth(), background.getHeight());
        this.getContentPane().add(background);


        this.getContentPane().repaint();
    }

    private void initFrame(){

        //设置界面大小
        this.setSize(480,430);
        //设置标题
        this.setTitle("拼图游戏 v1.00 登录");
        //让界面置顶
        this.setAlwaysOnTop(true);
        //让界面居中
        this.setLocationRelativeTo(null);
        //关闭程序之后自动关闭虚拟机
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);//this.setDefaultCloseOperation(3);


    }

    private void getNewCode(){
        String pattern = "qwertyuiopasdfghjklzxcvbnm1234567890";
        Random r = new Random();
        StringBuilder sb = new StringBuilder();
        for(int i = 0;i < 4;i++){
            sb.append(pattern.charAt(r.nextInt(pattern.length())));
        }
        RightCode = sb.toString();
        rightCodeButton.setText(RightCode);
    }


    @Override
    public void mouseClicked(MouseEvent e) {

        Object oj = e.getSource();

        //登录按键
        if(oj == login){
            String name = usernameText.getText();
            String pwd = pwdText.getText();
            String rightCode = rightCodeText.getText();
            System.out.println(rightCode);
            //判断密码、用户名、验证码是否为空
            if(name.isEmpty()){
                JOptionPane.showMessageDialog(this,"用户名不能为空！");
                getNewCode();
                return;
            }
            if(pwd.isEmpty()){
                JOptionPane.showMessageDialog(this,"密码不能为空！");
                getNewCode();
                return;
            }
            if(rightCode.isEmpty()){
                JOptionPane.showMessageDialog(this,"验证码不能为空！");
                getNewCode();
                return;
            }
            if(!rightCode.equals(RightCode)){
                //弹窗提示
                JOptionPane.showMessageDialog(this,"验证码错误！");
                rightCodeText.setText("");
                getNewCode();
                return;
            }
            if(!UserData.findUser(name,pwd)){
                JOptionPane.showMessageDialog(this,"用户名或密码错误！");
                pwdText.setText("");
                getNewCode();
                return;
            }else{
                new GameJFrame();
                this.setVisible(false);
            }

        }
        //注册按钮
        else if(oj == register){
            new RegisterJFrame();
            this.setVisible(false);
        }
        //更换验证码
        else if(oj == rightCodeButton){
            getNewCode();
        }

        //显示密码
        else if(oj == pwdVisible){
            if(!pwdVisible_flag){
                pwdVisible.setIcon(new ImageIcon("puzzlegame/img/login/显示密码按下.png"));
                pwdText.setEchoChar((char) 0);
                pwdVisible_flag = true;
            }
            else{
                pwdVisible.setIcon(new ImageIcon("puzzlegame/img/login/显示密码.png"));
                pwdText.setEchoChar('*');
                pwdVisible_flag = false;
            }
        }

    }

    @Override
    public void mousePressed(MouseEvent e) {
        Object oj = e.getSource();
        if(oj == login){
            login.setIcon(new ImageIcon("puzzlegame/img/login/登录按下.png"));
        }
        else if(oj == register){
            register.setIcon(new ImageIcon("puzzlegame/img/login/注册按下.png"));
        }
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        Object oj = e.getSource();
        //显示密码
        if(oj == login){
            login.setIcon(new ImageIcon("puzzlegame/img/login/登录按钮.png"));
        }
        //隐藏密码
        else if(oj == register){
            register.setIcon(new ImageIcon("puzzlegame/img/login/注册按钮.png"));
        }
    }

    @Override
    public void mouseEntered(MouseEvent e) {

    }

    @Override
    public void mouseExited(MouseEvent e) {

    }
}
