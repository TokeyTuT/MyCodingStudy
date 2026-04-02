package com.itheima.ui;

import cn.hutool.core.io.FileUtil;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.util.List;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;
import java.util.zip.ZipOutputStream;

public class NoteJFrame extends JFrame implements ActionListener {
    
    //数据源 —— 可以用配置文件代替
    String dataPath = "/Users/tuttokey/JavaProject/diary/diary/data.txt";
    
    List<String> list;
    //创建三个按钮
    JButton add = new JButton("添加");
    JButton update = new JButton("修改");
    JButton delete = new JButton("删除");

    //创建表格组件
    JTable table;



    //创建菜单的导入和导出
    JMenuItem exportItem = new JMenuItem("导出");
    JMenuItem importItem = new JMenuItem("导入");

    public NoteJFrame() {
        //加载数据
        readInfo();
        //初始化界面
        initFrame();
        //初始化菜单
        initJmenuBar();
        //初始化组件
        initView();
        //让界面显示出来
        this.setVisible(true);
    }

    private void readInfo() {
        list = FileUtil.readLines(dataPath, "UTF-8");

    }

    @Override
    public void actionPerformed(ActionEvent e) {
        //获取当前那个组件被点击
        Object obj = e.getSource();
        if(obj == add){
            System.out.println("添加按钮被点击");
            this.setVisible(false);
            new AddJFrame(list);

        }else if(obj == update){
            System.out.println("修改按钮被点击");
            //逻辑：
            //1.先判断用户有没有选择表格中的数据
            //2.如果没有选择，弹框提示：未选择。此时提示的弹框用showJDialog方法即可
            //3.如果选择了，跳转添加界面


            //获取用户选择了表格中的哪一行
            //i = 0: 表示用户选择了第一行
            //i = 1: 表示用户选择了第二行
            //i有两个作用：
            //i小于0，表示用户没有选择，此时无法修改
            //i大于等于0：通过这个行数就可以获取二维数组中对应的数据
            int i = table.getSelectedRow();
            System.out.println(i);
            if(i < 0){
                showJDialog("请先选择你要修改的行数！");
            }else{
                this.setVisible(false);
                new UpdateJFrame(i,list);
            }
        }else if(obj == delete){
            System.out.println("删除按钮被点击");
            //逻辑：
            //1.先判断用户有没有选择表格中的数据
            //2.如果没有选择，弹框提示：未选择。此时提示的弹框用showJDialog方法即可
            //3.如果选择了，弹框提示：是否确定删除。此时提示的弹框用showChooseJDialog方法

            int idx = table.getSelectedRow();
            if(idx < 0){
                showJDialog("请先选择你要删除的行");
                return;
            }

            //作用：展示一个带有确定和取消按钮的弹框
            //方法的返回值：0 表示用户点击了确定
            //             1 表示用户点击了取消
            //该弹框用于用户删除时候，询问用户是否确定删除
            if(showChooseJDialog() == 0) {
                list.remove(idx);
                FileUtil.writeLines(list, dataPath, "UTF-8");
                System.out.println(list);
                initView();
            }

        }else if(obj == exportItem){
            System.out.println("菜单的导出功能");
            try {
                ZipOutputStream zos = new ZipOutputStream(new FileOutputStream(new File("/Users/tuttokey/JavaProject","data.zip")));
                ZipEntry zn = new ZipEntry("data.txt");
                zos.putNextEntry(zn);
                FileInputStream fis = new FileInputStream(dataPath);
                int b;
                while((b = fis.read()) != -1){
                    zos.write(b);
                }
                fis.close();
                zos.closeEntry();
                zos.close();
            } catch (IOException ex) {
                showJDialog("导出失败");
                throw new RuntimeException(ex);
            }
            showJDialog("导出成功");
        }else if(obj == importItem){
            System.out.println("菜单的导入功能");
            try {
                ZipInputStream zis = new ZipInputStream(new FileInputStream("/Users/tuttokey/JavaProject/data.zip"));
                ZipEntry zn = zis.getNextEntry();
                FileOutputStream fos = new FileOutputStream(dataPath);
                int b;
                while((b = zis.read()) != -1){
                    fos.write(b);
                }
                zis.closeEntry();
                zis.close();
            } catch (IOException ex) {
                throw new RuntimeException(ex);
            }

            readInfo();
            initView();

            showJDialog("导入成功");

        }
    }

    //初始化组件
    private void initView() {

        //移除所有组件
        this.getContentPane().removeAll();

        //定义最上面的每日一记
        JLabel title = new JLabel("每日一记");
        title.setBounds(220, 20, 584, 50);
        title.setFont(new Font("宋体", Font.BOLD, 32));
        this.getContentPane().add(title);

        //定义表格的标题
        Object[] tableTitles = {"编号", "标题", "正文"};

        //定义表格的内容
        //二维数组中的每一个一维数组，是表格里面的一行数据
        Object[][] tableData = new Object[list.size()][3];
        for (int i = 0; i < list.size(); i++) {
            String[] split = list.get(i).split("&");
            String tit = split[0].split("=")[1];
            String content = split[1].split("=")[1];
            tableData[i] = new Object[]{Integer.toString(i + 1),tit,content};
        }

        //定义表格组件
        //并给表格设置标题和内容
        table = new JTable(tableData, tableTitles);
        table.setBounds(40, 70, 504, 380);

        //创建可滚动的组件，并把表格组件放在滚动组件中间
        //好处：如果表格中数据过多，可以进行上下滚动
        JScrollPane jScrollPane = new JScrollPane(table);
        jScrollPane.setBounds(40,70,504,380);
        this.getContentPane().add(jScrollPane);

        //给三个按钮设置宽高属性，并添加点击事件
        add.setBounds(40, 466, 140, 40);
        update.setBounds(222, 466, 140, 40);
        delete.setBounds(404, 466, 140, 40);

        add.setFont(new Font("宋体", Font.PLAIN, 24));
        update.setFont(new Font("宋体", Font.PLAIN, 24));
        delete.setFont(new Font("宋体", Font.PLAIN, 24));

        add.addActionListener(this);
        update.addActionListener(this);
        delete.addActionListener(this);


        this.getContentPane().add(add);
        this.getContentPane().add(update);
        this.getContentPane().add(delete);

        //刷新一下界面
        this.getContentPane().repaint();
    }

    //初始化菜单
    private void initJmenuBar() {
        //创建整个的菜单对象
        JMenuBar jMenuBar = new JMenuBar();
        //创建菜单上面的两个选项的对象 （功能  关于我们）
        JMenu functionJMenu = new JMenu("功能");

        //把5个存档，添加到saveJMenu中
        functionJMenu.add(exportItem);
        functionJMenu.add(importItem);

        //将菜单里面的两个选项添加到菜单当中
        jMenuBar.add(functionJMenu);

        //绑定点击事件
        exportItem.addActionListener(this);
        importItem.addActionListener(this);

        //给菜单设置颜色
        jMenuBar.setBackground(new Color(230,230,230));

        //给整个界面设置菜单
        this.setJMenuBar(jMenuBar);
    }

    //初始化界面
    private void initFrame() {
        //设置界面的宽高
        this.setSize(600, 600);
        //设置界面的标题
        this.setTitle("每日一记");
        //设置界面置顶
        this.setAlwaysOnTop(true);
        //设置界面居中
        this.setLocationRelativeTo(null);
        //设置关闭模式
        this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        //取消默认的居中放置，只有取消了才会按照XY轴的形式添加组件
        this.setLayout(null);
        //设置背景颜色
        this.getContentPane().setBackground(new Color(212,212,212));
    }

    //只创建一个弹框对象
    JDialog jDialog = new JDialog();
    //因为展示弹框的代码，会被运行多次
    //所以，我们把展示弹框的代码，抽取到一个方法中。以后用到的时候，就不需要写了
    //直接调用就可以了。
    //展示弹框
    public void showJDialog(String content) {
        if(!jDialog.isVisible()){
            //创建一个弹框对象
            JDialog jDialog = new JDialog();
            //给弹框设置大小
            jDialog.setSize(200, 150);
            //让弹框置顶
            jDialog.setAlwaysOnTop(true);
            //让弹框居中
            jDialog.setLocationRelativeTo(null);
            //弹框不关闭永远无法操作下面的界面
            jDialog.setModal(true);

            //创建Jlabel对象管理文字并添加到弹框当中
            JLabel warning = new JLabel(content);
            warning.setBounds(0, 0, 200, 150);
            jDialog.getContentPane().add(warning);

            //让弹框展示出来
            jDialog.setVisible(true);
        }
    }

    /*
    *  作用：展示一个带有确定和取消按钮的弹框
    *
    *  方法的返回值：
    *       0 表示用户点击了确定
    *       1 表示用户点击了取消
    *       该弹框用于用户删除时候，询问用户是否确定删除
    * */
    public int showChooseJDialog() {
        return JOptionPane.showConfirmDialog(this, "是否删除选中数据？","删除信息确认",JOptionPane.YES_NO_OPTION);
    }
}
