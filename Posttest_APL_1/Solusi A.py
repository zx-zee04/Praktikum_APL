while True:
    try:
        sisi1 = int(input("Masukkan panjang sisi 1: "))
        sisi2 = int(input("Masukkan panjang sisi 2: "))
        sisi3 = int(input("Masukkan panjang sisi 3: "))
        #mengecek apakah termasuk ketentuan segitiga
        valid = (sisi1 > 0 and sisi2 > 0 and sisi3 > 0) and (sisi1 + sisi2 > sisi3) and (sisi1 + sisi3 > sisi2) and (sisi2 + sisi3 > sisi1)
        if not valid:
            print("Sisi yang dimasukkan tidak valid dan tidak memenuhi ketentuan segitiga.")
            break
        
        else: #mengecek segitiga siku-siku
            siku_siku = (sisi1 ** 2 + sisi2 ** 2 == sisi3 ** 2) or (sisi1 ** 2 + sisi3 ** 2 == sisi2 ** 2) or (sisi2 ** 2 + sisi3 ** 2 == sisi1 ** 2)
            if siku_siku:
                jenis = "Segitiga siku-siku"
            #mengecek apakah termasuk segitiga sama kaki
            elif sisi1 == sisi2 or sisi1 == sisi3 or sisi2 == sisi3:
                jenis = "Segitiga sama kaki"
            #kalau tidak terdapat maka termasuk segitiga sembarang
            else:
                jenis = "Segitiga sembarang"

            print(f"Segitiga dengan sisi {sisi1}, {sisi2}, dan {sisi3} adalah {jenis}")
            break
    except ValueError:
        print("Masukkan bilangan bulat>")