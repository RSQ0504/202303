import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import read_wave;

public class file_chooser {
    public static void main(String[] args) {
        JFrame frame = new JFrame("Part");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 200);

        JButton button = new JButton("Open .wav File");
        button.setBounds(150, 70, 150, 30);

        JFileChooser file_window = new JFileChooser();

        FileNameExtensionFilter filter = new FileNameExtensionFilter("WAV", "wav");
        file_window.setFileFilter(filter);

        JPanel panel = new JPanel();
        panel.setLayout(new FlowLayout(FlowLayout.CENTER, 10, 10)); 
        panel.add(button);
        frame.add(panel);
        frame.setVisible(true);

        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int check = file_window.showOpenDialog(null);
                if (check == JFileChooser.APPROVE_OPTION) {
                    File file = file_window.getSelectedFile();
                    System.out.println("Selected .wav File: " + file.getPath());
                } else {
                    System.out.println("Wrong format");
                }
            }
        });
    }
}
