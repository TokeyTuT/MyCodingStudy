package www.tokeytut.ui;

import www.tokeytut.user.UserData;

import javax.swing.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

public class RegisterJFrame extends JFrame implements MouseListener {

    //图片
    private final JLabel usernamePhoto = new JLabel(new ImageIcon("puzzlegame/img/register/注册用户名.png"));
    private final JLabel pwdPhoto = new JLabel(new ImageIcon("puzzlegame/img/register/注册密码.png"));
    private final JLabel rePwdPhoto = new JLabel(new ImageIcon("puzzlegame/img/register/再次输入密码.png"));
    private final JLabel background = new JLabel(new ImageIcon("puzzlegame/img/register/background.png"));

    //按钮
    private final JButton register = new JButton(new ImageIcon("puzzlegame/img/register/注册按钮.png"));
    private final JButton reset = new JButton(new ImageIcon("puzzlegame/img/register/重置按钮.png"));

    //文本框
    private final JTextField username = new JTextField();
    private final JPasswordField password = new JPasswordField();
    private final JPasswordField rePassword = new JPasswordField();

    public RegisterJFrame() {
        //初始化界面
        initFrame();

        //初始化图形界面
        initView();

        //界面显示
        this.setVisible(true);
    }

    private void initView() {

        //用户名
        usernamePhoto.setBounds(80,130,79,17);
        this.getContentPane().add(usernamePhoto);
        username.setBounds(160,130,200,22);
        this.getContentPane().add(username);
        //密码
        pwdPhoto.setBounds(95,190,64,16);
        this.getContentPane().add(pwdPhoto);
        password.setBounds(160,190,200,22);
        password.setEchoChar('*');
        this.getContentPane().add(password);
        //重复密码
        rePwdPhoto.setBounds(65,250,96,17);
        this.getContentPane().add(rePwdPhoto);
        rePassword.setBounds(160,250,200,22);
        rePassword.setEchoChar('*');
        this.getContentPane().add(rePassword);

        //注册按钮
        register.setBounds(90,300,128,47);
        register.setBorderPainted(false);
        register.setContentAreaFilled(false);
        register.addMouseListener(this);
        this.getContentPane().add(register);

        //重置按钮
        reset.setBounds(260,300,128,47);
        reset.setBorderPainted(false);
        reset.setContentAreaFilled(false);
        reset.addMouseListener(this);
        this.getContentPane().add(reset);

        //设置背景
        background.setSize(470,390);
        this.getContentPane().add(background);

    }

    private void initFrame() {
        //设置界面大小
        this.setSize(480,420);
        //设置标题
        this.setTitle("注册");
        //让界面置顶
        this.setAlwaysOnTop(true);
        //让界面居中
        this.setLocationRelativeTo(null);
        //关闭程序之后自动关闭虚拟机
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);//this.setDefaultCloseOperation(3);
    }

    @Override
    public void mouseClicked(MouseEvent e) {
        Object oj = e.getSource();

        if(oj == register){
            String name = username.getText();
            String pwd = password.getText();
            String rePwd = rePassword.getText();

            if(!pwd.equals(rePwd)){
                JOptionPane.showMessageDialog(this,"两次密码输入不一致，请重新输入！");
                return;
            }
            if(name.isEmpty()){
                JOptionPane.showMessageDialog(this,"用户名不能为空！");
                return;
            }
            if(pwd.isEmpty()){
                JOptionPane.showMessageDialog(this,"密码不能为空！");
                return;
            }
            if(rePwd.isEmpty()){
                JOptionPane.showMessageDialog(this,"密码不能为空");
                return;
            }
            if(UserData.findUserName(name)){
                JOptionPane.showMessageDialog(this,"该用户已存在！");
                username.setText("");
                password.setText("");
                rePassword.setText("");
                return;
            }

            if(UserData.addUser(name,pwd)){
                JOptionPane.showMessageDialog(this,"添加成功！");
                UserData.printAllUser();
                new LoginJFrame();
            }
            else{
                JOptionPane.showMessageDialog(this,"添加异常！");
            }
        }

        if(oj == reset){
            username.setText("");
            password.setText("");
            rePassword.setText("");
        }
    }

    @Override
    public void mousePressed(MouseEvent e) {
        Object oj = e.getSource();

        if(oj == register){
            register.setIcon(new ImageIcon("puzzlegame/img/register/注册按下.png"));
        }
        else if(oj == reset){
            reset.setIcon(new ImageIcon("puzzlegame/img/register/重置按下.png"));
        }
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        Object oj = e.getSource();

        if(oj == register){
            register.setIcon(new ImageIcon("puzzlegame/img/register/注册按钮.png"));
        }
        else if(oj == reset){
            reset.setIcon(new ImageIcon("puzzlegame/img/register/重置按钮.png"));
        }
    }

    @Override
    public void mouseEntered(MouseEvent e) {

    }

    @Override
    public void mouseExited(MouseEvent e) {

    }

}
