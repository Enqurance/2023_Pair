import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;


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
        panel1.setLayout(null);
        panel1.setBounds(0, 0, 500, 300);
        add(panel1);


        JPanel panel2 = new JPanel();
        panel2.setLayout(null);
        panel2.setBounds(0, 300, 500, 300);
        add(panel2);

        JPanel panel3 = new JPanel();
        panel3.setLocation(500, 0);
        panel3.setSize(300, 600);
        add(panel3);


        /* 输入文本域设置 */
        JLabel inputLabel = new JLabel("输入框");
        inputLabel.setBounds(50, 30, 40, 20);
        panel1.add(inputLabel);
        JTextArea inputArea = new JTextArea();
        JScrollPane inputScrollPane = new JScrollPane(inputArea);   // 滚动条
        inputArea.setLineWrap(false);
        inputScrollPane.setBounds(50, 50, 400, 200);
        panel1.add(inputScrollPane);

        /* 输出文本域设置 */
        JLabel outputLabel = new JLabel("输出框");
        outputLabel.setBounds(50, 0, 40, 20);
        panel2.add(outputLabel);
        JTextArea outputArea = new JTextArea();
        outputArea.setEditable(false);
        JScrollPane outputScrollPane = new JScrollPane(outputArea);   // 滚动条
        outputArea.setLineWrap(false);
        outputScrollPane.setBounds(50, 20, 400, 200);
        panel2.add(outputScrollPane);

        /* 文件选择器FileChooser */
        JButton fileChooseButton = new JButton("选择文件");
        fileChooseButton.setBounds(50, 260, 80, 30);
        fileChooseButton.addActionListener(e -> {
            JFileChooser fileChooser = new JFileChooser();
            FileNameExtensionFilter filter = new FileNameExtensionFilter("Text Files", "txt");
            fileChooser.setFileFilter(filter);
            if (fileChooser.showOpenDialog(panel1) == JFileChooser.APPROVE_OPTION) {
                // Get the selected file
                java.io.File selectedFile = fileChooser.getSelectedFile();
                System.out.println("Selected file: " + selectedFile.getAbsolutePath());
                String context = readTxtFile(selectedFile.getAbsolutePath());
                inputArea.setText(context);
            }
        });
        panel1.add(fileChooseButton);

        /* 将输出框内容保存为文件 */
        JButton saveButton = new JButton("保存文件");
        saveButton.addActionListener(e -> {
            // 创建一个文件选择器，让用户选择保存文件的路径
            JFileChooser fileChooser = new JFileChooser();
            fileChooser.setDialogTitle("选择保存路径");
            fileChooser.setFileFilter(new FileNameExtensionFilter("Text files", "txt"));
            int userSelection = fileChooser.showSaveDialog(this);
            if (userSelection == JFileChooser.APPROVE_OPTION) {
                // 获取用户选择的文件路径
                File fileToSave = fileChooser.getSelectedFile();
                if (!fileToSave.getName().endsWith(".txt")) {
                    // 如果不是，弹出提示框，提示用户选择一个 .txt 文件
                    JOptionPane.showMessageDialog(this, "请选择一个 .txt 格式的文件！");
                }
                try {
                    FileWriter writer = new FileWriter(fileToSave);
                    writer.write(outputArea.getText());
                    writer.close();
                    JOptionPane.showMessageDialog(this, "文件保存成功！");
                } catch (IOException ex) {
                    JOptionPane.showMessageDialog(this, "保存文件失败：" + ex.getMessage());
                }
            }
        });
        saveButton.setBounds(50, 230, 80, 30);
        panel2.add(saveButton);

    }

    private String readTxtFile(String filepath) {
        StringBuilder str = new StringBuilder();
        try (BufferedReader br = new BufferedReader(new FileReader(filepath))) {
            String line;
            while ((line = br.readLine()) != null) {
                System.out.println(line);
                str.append(line);
            }
        } catch (IOException e) {
            System.err.println("Failed to read file: " + e.getMessage());
        }
        return str.toString();
    }
}