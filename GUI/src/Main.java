import java.awt.*;

import javax.swing.*;


public class Main {
    public static void main(String[] args) {
        new MyFrame().setVisible(true);
    }
}

class MyFrame extends JFrame {
    public MyFrame() {
        setTitle("Longest-Word-Chain");
        setSize(800, 600);
        setLocation(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setResizable(false);
        setFrameLayout();
    }

    private void setFrameLayout() {
        JPanel panel1 = new JPanel();
        panel1.setSize(500, 300);
        add(panel1, BorderLayout.WEST);

        JPanel panel2 = new JPanel();
        panel2.setLocation(0, 300);
        panel2.setSize(500, 300);
        add(panel2, BorderLayout.WEST);

        JPanel panel3 = new JPanel();
        panel3.setLocation(500, 0);
        panel3.setSize(300, 600);
        add(panel3, BorderLayout.EAST);

        JTextArea jta = new JTextArea("这是一段文本域");
    }

}