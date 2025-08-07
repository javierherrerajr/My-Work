// components/ReviewButton.tsx
import Link from "next/link";
import { Button } from "@/components/ui/button";

export const ReviewButton: React.FC<{ courseId: string }> = ({ courseId }) => (
  <Link href={`/review?courseId=${courseId}`}>
    <Button variant="default" className="!bg-[#B0C69A] hover:!bg-[#9DB68A] font-poppins font-semibold !text-[#2C1818] text-[14px] md:text-[18px] w-[200px] mb-3">
      Submit a Review
    </Button>
  </Link>
);

