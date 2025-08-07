import '@/styles/globals.css'
import Image from 'next/image'
import { Navbar } from '@/components/Navbar'

export default function Header() {
    return (
        <>
            <Navbar />
            <div className="flex justify-center pt-4">
                <Image src="/logo.svg" alt="logo" width={250} height={250} priority/>
            </div>
            <div className="w-screen mx-auto -ml-[50vw] -mr-[50vw] left-1/2 right-1/2 relative bg-[#D3DFC7] py-7">
                <h2 className="text-[25px] font-semibold font-baloo text-[#2C1818] text-center">
                    Real Reviews. Real Students. Real Classes.
                </h2>
            </div>
        </>
    )
}