'use client';

import { Button } from '@/components/ui/button';
import Link from 'next/link';
import { useSession, signOut } from 'next-auth/react';

export const Navbar: React.FC = () => {
  const { data: session, status } = useSession();

  const handleLogout = () => {
    signOut({ callbackUrl: '/home' });
  };

  return (
    <div className="w-screen mx-auto -ml-[50vw] -mr-[50vw] left-1/2 right-1/2 relative">
      <nav className="w-[100%] top-0 z-50 flex items-center justify-between px-4 md:px-8 h-[60px]">
        <div className="flex-shrink-0">
          <Link href="/home">
            <Button variant="default" className="!bg-[#B0C69A] hover:!bg-[#9DB68A] font-poppins font-semibold !text-[#2C1818] text-[14px] md:text-[18px]">
              home
            </Button>
          </Link>
        </div>
        
        <div className="flex items-center gap-2 md:gap-4">
          <Link href="/review">
            <Button variant="default" className="!bg-[#CDEAFF] hover:!bg-[#B3CDDF] font-poppins font-semibold !text-[#2C1818] text-[14px] md:text-[18px]">
              reviews
            </Button>
          </Link>
          
          {status === 'loading' ? (
            <div className="w-20 h-9 bg-gray-200 animate-pulse rounded"></div>
          ) : session ? (
            <div className="flex items-center gap-2">
              <Link href="/profile">
                <Button variant="default" className="!bg-[#B0C69A] hover:!bg-[#9DB68A] font-poppins font-semibold !text-[#2C1818] text-[14px] md:text-[18px]">
                  profile
                </Button>
              </Link>
              <Button 
                variant="default" 
                onClick={handleLogout}
                className="!bg-[#FF6B6B] hover:!bg-[#FF5252] font-poppins font-semibold !text-white text-[14px] md:text-[18px]"
              >
                logout
              </Button>
            </div>
          ) : (
            <Link href="/login">
              <Button variant="default" className="!bg-[#B0C69A] hover:!bg-[#9DB68A] font-poppins font-semibold !text-[#2C1818] text-[14px] md:text-[18px]">
                sign in
              </Button>
            </Link>
          )}
        </div>
      </nav>
    </div>
  );
};
