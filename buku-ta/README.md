# Buku Tugas Akhir
Buku Tugas Akhir menggunakan LaTeX

Soal : [FACTMODP](https://www.spoj.com/problems/FACTMODP)\
Oleh : Ferdinand Jason G (0511640000033)

Departemen Informatika, \
Fakultas Teknologi Informasi dan Komunikasi,\
ITS

## Outline
- [Buku Tugas Akhir](#buku-tugas-akhir)
    - [Outline](#outline)
    - [1. LaTeX](#1-latex)
        - [1.1. Definisi](#11-definisi)
        - [1.2. Instalisasi](#12-instalisasi)
            - [1.2.1. TexLive](#121-texlive)
            - [1.2.2. Visual Studio Code](#122-visual-studio-code)
    - [2. Buku Tugas Akhir](#2-buku-tugas-akhir)
        - [2.1. Bab 1](#21-bab-1)
        - [2.2. Bab 2](#22-bab-2)
        - [2.3. Bab 3](#23-bab-3)
        - [2.4. Bab 4](#24-bab-4)
        - [2.5. Bab 5](#25-bab-5)
        - [2.6. Bab 6](#26-bab-6)
        - [2.7. Bib](#27-bib)
        - [2.8. Language](#28-language)
            - [2.8.1 Hyphenation](#281-hyphenation)
        - [2.9. Pembuka](#29-pembuka)
            - [2.9.1. Abstrak](#291-abstrak)
            - [2.9.2. Daftar Isi](#292-daftar-isi)
            - [2.9.2. Daftar Notasi](#292-daftar-notasi)
            - [2.9.2. Kata Pengantar](#292-kata-pengantar)
            - [2.9.2. Lembar Pengesahan](#292-lembar-pengesahan)
            - [2.9.2. Sampul](#292-sampul)
        - [2.10. Penutup](#210-penutup)
            - [2.10.1. Daftar Pustaka](#2101-daftar-pustaka)
            - [2.10.2. Biodata](#2102-biodata)
        - [2.11. Util](#211-util)
            - [2.11.1 Packages](#2111-packages)
            - [2.11.2 Setting](#2112-setting)
            - [2.11.3 Styles](#2113-styles)
            - [2.11.4 Utils](#2114-utils)
            - [2.11.5 Variables](#2115-variables)

## 1. LaTeX
### 1.1. Definisi 
LaTeX adalah bahasa markup dokumen atau sistem penyiapan teks untuk membuat sebuah dokumen. LaTeX memungkinkan penggunanya melakukan *typesetting* dan mencetak hasil kerjanya dalam bentuk tipografi yang baik. LaTeX sangat cocok digunakan untuk membuat dokumen yang membutuhkan banyak pemformatan, seperti artikel ilmiah atau teknis, *paper*, laporan, tugas akhir, buku yang mengandung banyak rumus matematika atau *script* dan *code* program, serta skripsi, *thesis*, dan disertasi.
Compiler yang harus digunakan adalah `XeLaTeX`.

### 1.2. Instalisasi
Instalisasi LaTeX pada komputer.

#### 1.2.1. TexLive
1. Buka terminal
2. Install Tex Live

    ```bash
    sudo apt-get update
    sudo apt-get install texlive-full
    ```
3. Install Windows Fonts

    ```bash
    sudo apt-get install ttf-mscorefonts-installer
    sudo fc-cache -f -v
    ```
#### 1.2.2. Visual Studio Code
1. Install LaTeX Workspace pada Ekstension Visual Studio Code
2. Masukkan code pada `vscode.preferences` pada User.Preferences Visual Studio Code
```JSON
      "latex-workshop.latex.tools": [
        {
          "name": "latexmk_xe",
          "command": "latexmk",
          "args": [
            "-xelatex",
            "-synctex=1",
            "-interaction=nonstopmode",
            "-file-line-error",
            "%DOC%"
          ]
        },
      ],
      "latex-workshop.latex.recipes": [
        {
          "name": "latexmk_xe",
          "tools": [
            "latexmk_xe"
          ]
        },
      ],
```
3. CTRL + ALT + B untuk build pada `main.tex` dan instal semua kebutuhan LaTex
4. CTRL + ALT + V untuk view pdf pada `main.tex`

## 2. Buku Tugas Akhir
### 2.1. Bab 1
Digunakan sebagai penulisan untuk Bab 1 buku tugas akhir

### 2.2. Bab 2
Digunakan sebagai penulisan untuk Bab 2 buku tugas akhir

### 2.3. Bab 3
Digunakan sebagai penulisan untuk Bab 3 buku tugas akhir

### 2.4. Bab 4
Digunakan sebagai penulisan untuk Bab 4 buku tugas akhir

### 2.5. Bab 5
Digunakan sebagai penulisan untuk Bab 5 buku tugas akhir

### 2.6. Bab 6
Digunakan sebagai penulisan untuk Bab 6 buku tugas akhir

### 2.7. Bib
Digunakan sebagai cikal bakal dari daftar pustaka. 

### 2.8. Language
#### 2.8.1 Hyphenation
Digunakan untuk mendefinsikan hyphenation yang digunakan pada buku tugas akhir

### 2.9. Pembuka
#### 2.9.1. Abstrak
Digunakan untuk menuliskan abstraksi pada buku tugas akhir
#### 2.9.2. Daftar Isi
Digunakan untuk menuliskan daftar isi pada buku tugas akhir
#### 2.9.2. Daftar Notasi
Digunakan untuk menuliskan daftar notasi yang digunakan pada buku tugas akhir
#### 2.9.2. Kata Pengantar
Digunakan untuk menulis Kata Pengantar
#### 2.9.2. Lembar Pengesahan
Digunakan untuk menulis Lembar Pengesahan
#### 2.9.2. Sampul
Digunakan sebagai sampul pada buku tugas akhir

### 2.10. Penutup
#### 2.10.1. Daftar Pustaka
Digunakan untuk menuliskan daftar cite maupun bib pada LaTeX maupun buku tugas akhir.
#### 2.10.2. Biodata
Digunakan untuk menuliskan biodata penulis

### 2.11. Util
#### 2.11.1 Packages
Digunakan untuk mendefinsikan package yang digunakan pada project ini. Menggunakan keyword `\usepackage{}` pada LaTeX.
#### 2.11.2 Setting
Digunakan sebagai alternate user setting untuk mengoverride setting yang sudah ada.
#### 2.11.3 Styles
Digunakan sebagai alternate user styles untuk mengoverride styles yang sudah ada
#### 2.11.4 Utils
Digunakan sebagai utils pada buku tugas akhir.
#### 2.11.5 Variables
Digunakan untuk mendeklarasikan variable pada buku tugas akhir
