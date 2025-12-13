import numpy as np
import matplotlib.pyplot as plt
from PIL import Image, ImageDraw
import math
import os
from pathlib import Path

SCRIPT_DIR = Path(__file__).resolve().parent
REPO_ROOT = SCRIPT_DIR.parent
image_original = REPO_ROOT / 'dataset' / 'macaco.pgm'
image_new = REPO_ROOT / 'reconstruida.pgm'
bitstream_path = REPO_ROOT / 'bitstream.bin'

def get_file_size(file_path):
    """
    Função para calcular o tamanho de um arquivo em bytes.

    Args:
    file_path (str): Caminho para o arquivo.

    Returns:
    int: Tamanho do arquivo em bytes.
    """
    try:
        file_size = os.path.getsize(file_path)
        return file_size
    except OSError as e:
        print(f"Erro ao acessar o arquivo: {e}")
        return None

def calculate_mse(original_image, compressed_image):
    """
    Função para calcular o erro médio quadrático (MSE) entre duas imagens.

    Args:
    original_image (numpy array): imagem original.
    compressed_image (numpy array): imagem comprimida.

    Returns:
    float: MSE calculado.
    """
    if original_image.shape != compressed_image.shape:
        raise ValueError("As imagens devem ter as mesmas dimensões.")

    mse = np.mean((original_image - compressed_image) ** 2)
    return mse

def calculate_psnr(original_image, compressed_image, max_pixel_value=255.0):
    """
    Função para calcular o PSNR entre a imagem original e a imagem comprimida.

    Args:
    original_image (numpy array): imagem original.
    compressed_image (numpy array): imagem comprimida.
    max_pixel_value (float): valor máximo possível de um pixel na imagem (padrão 255).

    Returns:
    float: PSNR calculado.
    """
    mse = calculate_mse(original_image, compressed_image)
    if mse == 0:
        return float('inf')  # PSNR é infinito se não houver erro (as imagens são idênticas)

    psnr = 10 * math.log10((max_pixel_value ** 2) / mse)
    return psnr

def calculate_score(psnr, bitstream_size):
    """
    Função para calcular a pontuação com base na equação PSNR / log(bitstream_size).

    Args:
    psnr (float): valor de PSNR da imagem.
    bitstream_size (float): tamanho do bitstream do algoritmo (em bytes ou bits).

    Returns:
    float: pontuação calculada.
    """
    if bitstream_size <= 0:
        raise ValueError("O tamanho do bitstream deve ser maior que zero.")

    return psnr / math.log(bitstream_size)

# Função principal
def main():
    # Carregar a imagem original e a imagem comprimida
    if not image_original.exists():
        print(f"Erro: imagem original não encontrada: {image_original}")
        return
    image = Image.open(image_original).convert('L')
    image_np = np.array(image)

    # Reconstruir a imagem a partir do bytecode
    if not image_new.exists():
        print(f"Erro: imagem reconstruída não encontrada: {image_new}")
        return
    reconstructed_image = Image.open(image_new).convert('L')
    reconstructed_image_np = np.array(reconstructed_image)

    print(f"maior pixel da imagem reconstruída: {np.max(reconstructed_image_np)}")
    # Tamanho do bitstream

    bitstream_size = get_file_size(bitstream_path) # em bytes

    if bitstream_size is not None:
        print(f"Tamanho do arquivo: {bitstream_size} bytes")


    # print(np.max(image_np))
    psnr = calculate_psnr(image_np, reconstructed_image_np, max_pixel_value=255.0)
    print(f"PSNR: {psnr:.2f} dB")
    score = calculate_score(psnr, bitstream_size)
    print(f"Score: {score:.4f}")

    # Exibir imagens
    plt.figure(figsize=(18, 6))

    plt.subplot(1, 2, 1)
    plt.title('Imagem de Entrada (I)')
    plt.imshow(image_np, cmap='gray')

    plt.subplot(1, 2, 2)
    plt.title('Imagem Reconstruída (R)')
    plt.imshow(reconstructed_image_np, cmap='gray')


    plt.show()

if __name__ == "__main__":
    main()
