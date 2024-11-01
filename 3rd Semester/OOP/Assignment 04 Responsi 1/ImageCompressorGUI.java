package compressor;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import javax.swing.*;
import javax.swing.border.EmptyBorder;

public class ImageCompressorGUI extends JFrame implements ActionListener {
    private final JLabel statusLabel;
    private final JLabel imagePreview;
    private File selectedFile;
    private final ImageCompressor compressor;
    private final FileHandlerCompress fileHandler;
    private final JSlider qualitySlider;

    public ImageCompressorGUI() {
        compressor = new ImageCompressor();
        fileHandler = new FileHandlerCompress();

        setTitle("Image Compressor");
        setSize(600, 400);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        JButton selectButton = new JButton("Select Image");
        selectButton.addActionListener(e -> selectImage());

        JButton compressButton = new JButton("Compress Image");
        compressButton.addActionListener(this);

        JPanel buttonPanel = new JPanel();
        buttonPanel.add(selectButton);
        buttonPanel.add(compressButton);

        statusLabel = new JLabel("Status: No file selected");

        add(buttonPanel, BorderLayout.SOUTH);
        add(statusLabel, BorderLayout.CENTER);
    }

    private void selectImage() {
        selectedFile = fileHandler.chooseFile();
        if (selectedFile != null) {
            statusLabel.setText("Selected file: " + selectedFile.getName());
        } else {
            statusLabel.setText("No file selected");
        }
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (selectedFile != null) {
            try {
                File outputFile = new File("compressed_" + selectedFile.getName());
                compressor.compressImage(selectedFile, outputFile, 0.7f);
                statusLabel.setText("Image compressed to: " + outputFile.getPath());
            } catch (Exception ex) {
                statusLabel.setText("Error: Unsupported Format. Use either .jpg or .png");
            }
        } else {
            statusLabel.setText("Please select an image first.");
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            ImageCompressorGUI gui = new ImageCompressorGUI();
            gui.setVisible(true);
        });
    }
}
