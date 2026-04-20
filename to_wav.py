import argparse
import csv
import os.path
import wave
import struct

def clamp(x: float, lo: float, hi: float) -> float:
    if x < lo:
        return lo
    if x > hi:
        return hi
    return x

def read_csv_samples(path: str):
    samples = []
    with open(path, "r", newline="") as f:
        r = csv.reader(f)
        for row in r:
            if not row:
                continue
            s = row[0].strip()
            if s == "":
                continue
            samples.append(float(s))
    return samples

def write_wav(path: str, samples, rate: int, gain: float, normalize: bool):
    if not samples:
        raise ValueError("CSV has no samples.")

    scaled = [x * gain for x in samples]

    if normalize:
        max_abs = max(abs(x) for x in scaled)
        if max_abs > 0.0:
            scaled = [x / max_abs for x in scaled]

    with wave.open(path, "wb") as wf:
        wf.setnchannels(1)
        wf.setsampwidth(2)
        wf.setframerate(rate)

        for x in scaled:
            x = clamp(x, -1.0, 1.0)
            pcm = int(round(x * 32767.0))
            wf.writeframes(struct.pack("<h", pcm))

def main():
    p = argparse.ArgumentParser()
    p.add_argument("--input", required=True, help="Input CSV (one sample per line)")
    p.add_argument("--output", default=None, help="Output WAV")
    p.add_argument("--rate", type=int, default=44100, help="Sample rate (Hz)")
    p.add_argument("--gain", type=float, default=1.0, help="Multiply all samples by this factor")
    p.add_argument("--normalize", action="store_true", help="Normalize to full scale (removes amplitude differences)")
    args = p.parse_args()

    if os.path.isdir(args.input):
        csv_files = [file for file in os.listdir(args.input) if file.endswith('.csv')]
        for csv_file in csv_files:
            in_csv = os.path.join(args.input, csv_file)
            out_wav = os.path.join(args.input, csv_file.replace('.csv', '.wav'))
            samples = read_csv_samples(in_csv)
            write_wav(out_wav, samples, args.rate, args.gain, args.normalize)

    else:
        output = args.input.replace('.csv', '.wav') if args.output is None else args.output
        samples = read_csv_samples(args.input)
        write_wav(output, samples, args.rate, args.gain, args.normalize)

if __name__ == "__main__":
    main()
